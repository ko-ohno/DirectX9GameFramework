/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Renderer.h] レンダラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：レンダラークラス
=============================================================================*/
#ifndef RENDERER_H_
#define	RENDERER_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "../Math.h"
#include "ResourceManager/EffectManager.h"

/*-------------------------------------
/* レンダラークラス
-------------------------------------*/
class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer(void);

	static Renderer* Create(class Game* game);

	bool StartUp(void);
	void ShutDown(void);

	void Update(float deltaTime);
	void Draw(void);

private:
	void DrawUpRendererComponents(class Camera* camera, int nowDrawLayerOrder);

public:
	//
	// レンダラーコンポーネントのポインタの追加と削除
	//

	void AddRendererComponentAddress(class RendererComponent* rendererComponent);
	void RemoveRendererComponentAddress(class RendererComponent* rendererComponent);

	//
	// レンダラーコンポーネントのポインタの追加と削除
	//

	void AddCameraGameObjectAddress(class Camera* cameraGameObject);
	void RemoveCameraGameObjectAddress(class Camera* cameraGameObject);


	//レンダラーコンポーネントのソート
	void SortByRendererComponent(void);

	class Game* GetGame(void) { return game_; }

private:
	//レンダラーの所有者
	class Game* game_;	

	//シェーダの管理者
	class ShaderManager* shader_manager_;

	//エフェクトの管理者
	class EffectManager* effect_manager_;

	//Effekseerのエフェクト描画用レンダラー
	class EffekseerRendererDX9::Renderer* effekseer_renderer_;

	//画面の高さ、幅、画面倍率
	int	  screen_width_;
	int	  screen_height_;
	float screen_scaler_;

	//カメラのゲームオブジェクトの稼働コンテナ
	std::vector<class Camera*> camera_game_objects_;

	//レンダラーコンポーネントの稼働コンテナ
	std::vector<class RendererComponent*> renderer_components_;

	//カメラ現在座標が、１フレーム前と違う場合、ソートをする
	Vector3 now_camera_pos_; 
	Vector3 old_camera_pos_; 	
};	

#endif //RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/