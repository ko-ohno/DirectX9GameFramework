/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[RendererComponent.h] レンダラーコンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レンダラーコンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef RENDER_COMPONENT_H_
#define	RENDER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"
#include "../../Game.h"
#include "../../ResourceManager/ShaderManager.h"
#include "../../ResourceManager/TextureManager.h"
#include "../../ResourceManager/MeshManager.h"
#include "../../ResourceManager/EffectManager.h"
#include "../../../DX9Graphics.h"
#include "../../VertexData.h"
#include "../Component/TransformComponent.h"

/*-------------------------------------
/* レンダラーが保有されるレイヤーの型
-------------------------------------*/
enum class RendererLayerType
{
	None = -1
	, Sky				//スカイボックスなどメッシュ
	, BackGround		//背景となる地上などのメッシュ
	, Game				//ゲーム用のオブジェクト(メッシュやビルボード)が配置されるレイヤー
	, ParticleEffect	//パーティクル用(加算合成エフェクトなど)のレイヤー
	, UI				//HUDやタイトル画面など
	, Fade				//フェード用のレイヤー

	, Max
};

/*-------------------------------------
/* レンダラーコンポーネントのベースクラス
-------------------------------------*/
class RendererComponent : public Component
{
public:
	RendererComponent(class GameObject* owner, int drawOrder = 100);
	~RendererComponent(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;
	virtual void Draw(class Shader* shader, class Camera* camera);

public:

	void SetVertexColor(int red = 255, int green = 255, int blue = 255, int alpha = 255)
	{
		vertex_color_ = D3DCOLOR_RGBA(red, green, blue, alpha);

		vector_vertex_color_.x = DIVIDE_COLOR_VALUE * red;
		vector_vertex_color_.y = DIVIDE_COLOR_VALUE * green;
		vector_vertex_color_.z = DIVIDE_COLOR_VALUE * blue;
		vector_vertex_color_.w = DIVIDE_COLOR_VALUE * alpha;

		vector_vertex_color_.x = Math::Clamp(vector_vertex_color_.x, 0.f, 1.f);
		vector_vertex_color_.y = Math::Clamp(vector_vertex_color_.y, 0.f, 1.f);
		vector_vertex_color_.z = Math::Clamp(vector_vertex_color_.z, 0.f, 1.f);
		vector_vertex_color_.w = Math::Clamp(vector_vertex_color_.w, 0.f, 1.f);
	}

	inline D3DXVECTOR4* GetVertexColor(void) { return &vector_vertex_color_; }

public:
	//姿勢制御の関数群

	//平行移動成分の操作

	inline void SetTranslation(float posX, float posY, float posZ = 0.f) { position_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetTranslationX(float posX) { position_.x = posX; }
	inline void SetTranslationY(float posY) { position_.y = posY; }
	inline void SetTranslationZ(float posZ) { position_.z = posZ; }

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ = 0.f) { position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	inline void AddTranslationX(float addValueX) { position_.x = addValueX; }
	inline void AddTranslationY(float addValueY) { position_.y = addValueY; }
	inline void AddTranslationZ(float addValueZ) { position_.z = addValueZ; }

	inline D3DXVECTOR3* GetPosition(void) { return &position_; }

	//拡縮成分の操作

	inline void SetScale(float scaleValue) { scale_ = { scaleValue, scaleValue, scaleValue }; }
	inline void SetScale(float scaleX, float scaleY, float scaleZ = 1.f) { scale_ = { scaleX, scaleY, scaleZ }; }
	inline void SetScale(const D3DXVECTOR3& scale) { scale_ = scale; }
	inline void SetScaleX(float scaleX) { scale_.x = scaleX; }
	inline void SetScaleY(float scaleY) { scale_.y = scaleY; }
	inline void SetScaleZ(float scaleZ) { scale_.z = scaleZ; }

	inline void AddScale(float addValueX, float addValueY, float addValueZ = 0.f) { scale_ += { addValueX, addValueY, addValueZ }; }
	inline void AddScale(const D3DXVECTOR3& addValue) { scale_ += addValue; }
	inline void AddScaleX(float addValueX) { scale_.x = addValueX; }
	inline void AddScaleY(float addValueY) { scale_.y = addValueY; }
	inline void AddScaleZ(float addValueZ) { scale_.z = addValueZ; }

	inline D3DXVECTOR3* GetScale(void) { return &scale_; }

public: 
	// このコンポーネントの回転を取得
	inline void SetRotationMatrix(const D3DXMATRIX& rotationMatrix) { rotation_matrix_ = rotationMatrix; }
	inline D3DXMATRIX* GetRotationMatrix(void) { return &rotation_matrix_; }

	// このコンポーネントのワールド座標情報を取得
	inline D3DXMATRIX* GetWorldMatrix(void) { return &world_matrix_; }

	// このコンポーネントの型
	inline TypeID GetComponentType(void) const override { return TypeID::RendererComponent; }
	
	// このコンポーネントがレンダリングされる描画レイヤーの設定
	inline void SetRendererLayerType(RendererLayerType rendererLayerType) { renderer_layer_type_ = rendererLayerType; }
	inline RendererLayerType GetRendererLayerType(void) const { return renderer_layer_type_; }

	// このコンポーネントがレンダリングされるシェーダーの種類
	inline ShaderType GetShaderType(void) const { return shader_type_; }
	inline void SetShaderType(ShaderType shaderType) { shader_type_ = shaderType; }

	// 描画命令順位:数値が大きいほど描画順位が高い
	inline int GetDrawOrder(void) const   { return draw_order_; }

	// 所有者の姿勢制御の影響を受けるか？
	inline void SetOwnerTransfromOrder(bool isOwnerTransformOrder) { is_owner_transform_order_ = isOwnerTransformOrder; }

	// カメラからの距離
	inline float GetCameraDistance(void) const { return camera_distance_; }
	inline void SetCameraDistance(float cameraDistance) { camera_distance_ = cameraDistance; }


protected:
	//
	//　Renderer用の情報
	//

	// 描画するレイヤーの種類
	RendererLayerType renderer_layer_type_;

	// 描画されるシェーダーの種類
	ShaderType shader_type_;

	// 描画の優先順位
	int draw_order_;

	// カメラまでの距離
	float camera_distance_;

protected:
	static constexpr float DIVIDE_COLOR_VALUE = 1.f / 255.f;

	//頂点カラー
	D3DCOLOR	vertex_color_;

	D3DXVECTOR4 vector_vertex_color_;

	//
	// RendererComponentの姿勢情報
	//

	bool is_owner_transform_order_;

	//回転情報
	D3DXMATRIX rotation_matrix_;

	//ワールド座標
	D3DXMATRIX world_matrix_;

	//座標
	D3DXVECTOR3 position_;

	//ポリゴンのサイズ
	D3DXVECTOR3 scale_;
};

#endif //RENDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/