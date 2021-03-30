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
#include "../../Manager/ShaderManager.h"
#include "../../Manager/TextureManager.h"
#include "../../../DX9Graphics.h"
#include "../../VertexData.h"

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

	//初期化
	bool Init(void) override;

	//終了化
	void Uninit(void) override;
	
	//更新処理
	void Update(float deltaTime) override;

	//描画処理
	virtual void Draw(class Shader* shader, class Camera* camera);

	//カメラ距離の算出
	float CalculationCameraDistance(class Camera* camera);

public:

	void SetVertexColor(int red = 255, int green = 255, int blue = 255, int alpha = 255)
	{
		vertex_color_ = D3DCOLOR_RGBA(red, green, blue, alpha);
	}

	void SetVertexColor(D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255))
	{
		vertex_color_ = color;
	}


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

	inline D3DXVECTOR3 GetPositon(void) const { return position_; }

	//拡縮成分の操作

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

	inline D3DXVECTOR3 GetScale(void) const { return scale_; }

public:

	// このコンポーネントの型
	inline TypeID GetComponentType(void) const override { return TypeID::RendererComponent; }
	
	// このコンポーネントがレンダリングされる描画レイヤーの種類
	inline RendererLayerType GetRendererLayerType(void) const { return renderer_layer_type_; }

	// このコンポーネントがレンダリングされるシェーダーの種類
	inline ShaderType GetShaderType(void) const { return shader_type_; }

	// 描画命令順位:数値が大きいほど描画順位が高い
	inline int GetDrawOrder(void) const   { return draw_order_; }

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

	//頂点カラー
	D3DCOLOR vertex_color_;

	//
	// RendererComponentの姿勢情報
	//

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