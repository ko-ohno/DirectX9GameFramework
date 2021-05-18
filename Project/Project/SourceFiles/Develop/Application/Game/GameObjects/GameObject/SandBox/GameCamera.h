/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameCamera.h] ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオブジェクト
=============================================================================*/
#ifndef GameCamera_H_
#define	GameCamera_H_

/*--- インクルードファイル ---*/
#include "../Camera.h"

/*-------------------------------------
/* クラス
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
};


#endif //GameCamera_H_
/*=============================================================================
/*		End of File
=============================================================================*/