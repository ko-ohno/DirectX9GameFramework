/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SandBox.h] ゲームを構成するゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームを構成するゲームオブジェクト
=============================================================================*/
#ifndef SAND_BOX_H_
#define	SAND_BOX_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* ゲームを構成するゲームオブジェクト
-------------------------------------*/
class SandBox : public GameObject
{
public:
	SandBox(class Game* game);
	~SandBox(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Actor; }

protected:
	class MoveComponent* move_component_;
};


#endif //SandBox_H_
/*=============================================================================
/*		End of File
=============================================================================*/