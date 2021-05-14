/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraTest.h] カメラテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラテスト用ゲームオブジェクト
=============================================================================*/
#ifndef CAMERA_TEST_H_
#define	CAMERA_TEST_H_

/*--- インクルードファイル ---*/
#include "../Camera.h"

/*-------------------------------------
/* カメラテスト用ゲームオブジェクト
-------------------------------------*/
class CameraTest : public Camera
{
public:
	CameraTest(class Game* game);
	~CameraTest(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::CameraTest; }

private:
};


#endif //CAMERA_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/