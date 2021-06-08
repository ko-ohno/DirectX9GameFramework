 /*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Renderer.cpp] レンダラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レンダラークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "Renderer.h"
#include "GameObjects/GameObject/Camera.h"
#include "GameObjects/Component/RendererComponent.h"
#include "ResourceManager/EffectManager.h"

#include "Shader/DissolveShader.h"

#include "Shader/SpriteShader.h"

#include "Shader/BillboardShader.h"

#include "Shader/StdMeshShader.h"
#include "Shader/SkinMeshShader.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Renderer::Renderer(Game* game)
	: game_(game)
	, shader_manager_(nullptr)
	, effect_manager_(nullptr)
	, effekseer_renderer_(nullptr)
	, screen_width_(100)
	, screen_height_(100)
	, screen_scaler_(0.f)
	, now_camera_pos_(0.f, 0.f, 0.f)
	, old_camera_pos_(now_camera_pos_)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Renderer::~Renderer(void)
{
	this->ShutDown();
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
Renderer* Renderer::Create(Game* game)
{
	return NEW Renderer(game);
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool Renderer::StartUp(void)
{
	//カメラのゲームオブジェクトのコンテナを初期化
	camera_game_objects_.clear();

	//レンダラーコンポーネントのコンテナを初期化
	renderer_components_.clear();
	
	//マネージャーの取得
	{
		//シェーダーのマネージャーの取得
		this->shader_manager_ = game_->GetShaderManager();
		const bool shader_manager_init_failed = (shader_manager_ == nullptr);
		if (shader_manager_init_failed)
		{
			assert(!"Renderer::StartUp()：シェーダーのマネージャーの取得に失敗しました！");
			return false;
		}

		//エフェクトのマネージャーの取得
		this->effect_manager_ = game_->GetEffectManager();
		const bool effect_manager_init_failed = (effect_manager_ == nullptr);
		if (effect_manager_init_failed)
		{
			assert(!"Renderer::StartUp()：エフェクトのマネージャーの取得に失敗しました！");
			return false;
		}

		//Effekseerの描画レンダラーを取得
		this->effekseer_renderer_ = effect_manager_->GetEffekseerRenderer();
		const bool effekseer_renderer_init_failed = (effekseer_renderer_ == nullptr);
		if (effekseer_renderer_init_failed)
		{
			assert(!"Renderer::StartUp()：Effekseerの描画レンダラーの取得に失敗しました！");
			return false;
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void Renderer::ShutDown(void)
{
	//
	// 定義する必要なし。
	//
	// Game.cppのほうでゲームオブジェクトを一括破棄しているので
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void Renderer::Update(void)
{

}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void Renderer::Draw(void)
{
	//レンダラーコンポーネントの描画
	int now_draw_layer_order = 0;
	int camera_counter_ = 0;

	//一度だけRendererLayerTypeのUIレイヤーとFadeレイヤーを描画するフラグ
	bool is_2Dlayer_draw_one_time = false;
	
	//描画レイヤー分繰り返す
	for (now_draw_layer_order
		;   now_draw_layer_order < static_cast<int>(RendererLayerType::Max)
		; ++now_draw_layer_order)
	{
		//カメラのインスタンス数だけ描画する
		for (auto camera_game_object : camera_game_objects_)
		{
		
			//RendererLayerTypeのUIレイヤーとFadeレイヤーを描画するか？
			is_2Dlayer_draw_one_time = ((camera_counter_ != 0)
										&& now_draw_layer_order >= static_cast<int>(RendererLayerType::UI));

			if (is_2Dlayer_draw_one_time)
			{
				continue;
			}

			//レンダラーコンポーネントのソート
			const bool is_camera_moved = camera_game_object->IsGetCameraMoved();
			if (is_camera_moved == true)
			{
				D3DXVECTOR3 camera_position;
				D3DXMATRIX  view_matrix = *camera_game_object->GetViewMatrix();
				D3DXMATRIX  projection_matrix = *camera_game_object->GetProjection3DMatrix();

				//ビュー行列を逆行列にしてカメラ座標を取り出す
				{
					//view_matrix = 
					D3DXMatrixInverse(&view_matrix, nullptr, &view_matrix);

					camera_position.x = view_matrix._41;
					camera_position.y = view_matrix._42;
					camera_position.z = view_matrix._43;
				}

				//カメラ座標と描画オブジェクトの座標の距離を計算
				for (auto renderer_component : renderer_components_)
				{
					auto rc_position = *renderer_component->GetPosition();

					//レンダラーコンポーネントとカメラの距離を計測
					auto dir = rc_position - camera_position;
					auto vec_length = D3DXVec3Length(&dir);
					{
						//カメラまでの距離を設定　
						renderer_component->SetCameraDistance(vec_length);
					}
				}

				//ソートを行う
				this->SortByRendererComponent();
			}

			//エフェクトの描画レイヤーの時に描画
			if (now_draw_layer_order == static_cast<int>(RendererLayerType::ParticleEffect))
			{
				auto camera_matrix		= effect_manager_->Convert44Matrix(*camera_game_object->GetViewMatrix());
				auto projection_matrix	= effect_manager_->Convert44Matrix(*camera_game_object->GetProjection3DMatrix());
				{
					//	カメラ行列と射影行列を変換して渡す
					effekseer_renderer_->SetCameraMatrix(camera_matrix);
					effekseer_renderer_->SetProjectionMatrix(projection_matrix);

					//Effekseerの描画レンダラーによるEffectRendererComponentの描画
					effekseer_renderer_->BeginRendering();
					{
						//レンダラーコンポーネントの描画処理
						this->DrawUpRendererComponents(camera_game_object, now_draw_layer_order);
					}
					effekseer_renderer_->EndRendering();
				}
			}
			else
			{
				//レンダラーコンポーネントの描画処理
				this->DrawUpRendererComponents(camera_game_object, now_draw_layer_order);
			}

			//何個目のカメラか？
			camera_counter_++;

		}
	}
}

/*-----------------------------------------------------------------------------
/* レンダラーコンポーネントの描画処理
-----------------------------------------------------------------------------*/
void Renderer::DrawUpRendererComponents(Camera* camera, int nowDrawLayerOrder)
{
	//コンポーネントの総描画
	for (auto renderer_component : renderer_components_)
	{
		//レンダラーのレイヤーの情報を取得
		auto renderer_layer_type = renderer_component->GetRendererLayerType();

		//描画命令中のレイヤーとレンダラーのレイヤーが等しい時描画
		if (static_cast<int>(renderer_layer_type) == nowDrawLayerOrder)
		{
			//シェーダーのセット
			auto shader_type = renderer_component->GetShaderType();
			if (shader_type == ShaderType::None)
			{
				assert(!"DrawUpRendererComponents():不正なシェーダーが設定されています。");
			}
			auto shader = shader_manager_->ShaderDispatch(shader_type); //定数キーからシェーダを取得

			//シェーダを使用したコンポーネントの描画
			renderer_component->Draw(shader, camera);
		}
	}
}

/*-----------------------------------------------------------------------------
/* レンダラーコンポーネントのアドレスの追加処理
-----------------------------------------------------------------------------*/
void Renderer::AddRendererComponentAddress(RendererComponent* rendererComponent)
{
	//描画優先順位
	RendererLayerType my_layer_type = rendererComponent->GetRendererLayerType();
	int				  my_draw_order = rendererComponent->GetDrawOrder();

	//挿入できるまでコンポーネントの検索
	auto iter = renderer_components_.begin();
	for (;
		iter != renderer_components_.end();
		++iter)
	{
		if (my_layer_type == (*iter)->GetRendererLayerType())
		{
			if (my_draw_order > (*iter)->GetDrawOrder())
			{
				break;
			}
		}
	}
	renderer_components_.insert(iter, rendererComponent);	//挿入
}

/*-----------------------------------------------------------------------------
/* レンダラーコンポーネントのアドレスの削除処理
-----------------------------------------------------------------------------*/
void Renderer::RemoveRendererComponentAddress(RendererComponent* rendererComponent)
{
	auto iter = std::find(renderer_components_.begin()	//範囲0～
						 , renderer_components_.end()	//範囲最大まで
						 , rendererComponent);			//探す対象

	if (iter != renderer_components_.end())
	{
		renderer_components_.erase(iter);
	}
}

/*-----------------------------------------------------------------------------
/* レンダラーにカメラのアドレス追加処理
-----------------------------------------------------------------------------*/
void Renderer::AddCameraGameObjectAddress(Camera* cameraGameObject)
{
	camera_game_objects_.emplace_back(cameraGameObject);
}

/*-----------------------------------------------------------------------------
/* レンダラーのカメラのアドレス削除処理
-----------------------------------------------------------------------------*/
void Renderer::RemoveCameraGameObjectAddress(Camera* cameraGameObject)
{
	auto iter = std::find(camera_game_objects_.begin()	//範囲0～
						 , camera_game_objects_.end()	//範囲最大まで
						 , cameraGameObject);			//探す対象

	if (iter != camera_game_objects_.end())
	{
		camera_game_objects_.erase(iter);
	}
}

//
// ソート用に演算子を拡張
//
//bool operator < (const RendererComponent& left, const RendererComponent& right)
//{
//	//「奥　> 手前」の順に描画していく。
//	//「レイヤー　> 描画優先度　> カメラ距離」の順に描画していく
//	//以下のソートの手順は、比較した値どうしのうち、値が小さい(優先順位が高い)ほうから描画していく
//	{
//		//比較した値どうしが、同じレイヤーだった時。
//		if (static_cast<int>(left.GetRendererLayerType())
//			== static_cast<int>(right.GetRendererLayerType()))
//		{
//			//比較した値どうしが、同じ描画優先度だった時。
//			if (left.GetDrawOrder() == right.GetDrawOrder())
//			{
//				//比較した値どうしが、カメラ距離
//				if (left.GetCameraDistance() < right.GetCameraDistance()) { return true; }
//			}
//			if (left.GetDrawOrder() < right.GetDrawOrder()) { return true; }
//		}
//
//		//比較した値どうしが、違うレイヤーだった場合。
//		if (static_cast<int>(left.GetRendererLayerType())
//			< static_cast<int>(right.GetRendererLayerType()))
//		{
//			return true;
//		}
//	}
//	return false;
//}

/*-----------------------------------------------------------------------------
/* レンダラーコンポーネントのソート処理
-----------------------------------------------------------------------------*/
void Renderer::SortByRendererComponent(void)
{
	//ソート用選別関数を使用したマージソート
	std::stable_sort(
		renderer_components_.begin()
		, renderer_components_.end()
		, [](const RendererComponent* left, const RendererComponent* right)
		{
			if (static_cast<int>(left->GetRendererLayerType())
				== static_cast<int>(right->GetRendererLayerType()))
			{
 
				//比較した値どうしが、同じ描画優先度だった時。
				if (left->GetDrawOrder() == right->GetDrawOrder())
				{
					//カメラ距離によるソート
					return left->GetCameraDistance() > right->GetCameraDistance();
				}
				else
				{
					//描画オーダーによるソート
					return left->GetDrawOrder() < right->GetDrawOrder();
				}
			}
			else
			{
				//描画レイヤーによるソート
				return static_cast<int>(left->GetRendererLayerType()) < static_cast<int>(right->GetRendererLayerType());
			}
		}
	);
}

/*=============================================================================
/*		End of File
=============================================================================*/