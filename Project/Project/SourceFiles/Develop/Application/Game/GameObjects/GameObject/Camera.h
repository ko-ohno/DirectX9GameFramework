/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Camera.h] カメラのゲームオブジェクトのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラのゲームオブジェクトのベースクラス
=============================================================================*/
#ifndef CAMERA_H_
#define	CAMERA_H_

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "../GameObject.h"
#include "../../../Math.h"

/*-------------------------------------------
/* カメラのゲームオブジェクトのベースクラス
-------------------------------------------*/
class Camera : public GameObject
{
public:
	Camera(class Game* game);
	~Camera(void);

	bool Init(void);
	void Uninit(void);

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	//位置情報の取得

	//行列関係
	D3DXMATRIX* GetViewMatrix(void);		
	D3DXMATRIX* GetViewInverseMatrix(void);
	D3DXMATRIX* GetProjection2DMatrix(void);
	D3DXMATRIX* GetProjection3DMatrix(void);

	bool IsGetCameraMoved(void) const;

	virtual TypeID GetType(void) const { return TypeID::Camera; }

protected:
	class Game* game_;

	class CameraComponent* camera_component_;

	//カメラが動いたか
	bool is_moved_;

	D3DXVECTOR3 position_
			  , old_position_;
};


#endif //CAMERA_H_
/*=============================================================================
/*		End of File
=============================================================================*/