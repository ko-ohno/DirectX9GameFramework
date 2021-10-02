/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameCamera.h] カメラゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラゲームオブジェクト
=============================================================================*/
#ifndef GameCamera_H_
#define	GameCamera_H_

/*--- インクルードファイル ---*/
#include "../Camera.h"

/*-------------------------------------
/* カメラゲームオブジェクト
-------------------------------------*/
class GameCamera : public Camera
{
public:
	GameCamera(class Game* game);
	~GameCamera(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameCamera; }

private:
	static constexpr float MAX_CAMERA_ANIMATION_TIME = 10.f;

	float camera_animation_time_;

private:
	// 注視点座標のギズモ
	class BoxGizmoRendererComponent* lookat_point_gizmo_;

	// 上がるか下がるか
	bool is_move_top_;
	bool is_move_bottom_;

	// 値を上回るか、下回るか
	bool is_value_over_;
	bool is_value_under_;

	// 垂直
	float vertical_camera_shake_;
};


#endif //GameCamera_H_
/*=============================================================================
/*		End of File
=============================================================================*/