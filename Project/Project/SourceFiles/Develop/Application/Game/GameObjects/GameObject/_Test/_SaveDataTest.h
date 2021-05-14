/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataTest.h] セーブデータテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：セーブデータテスト用ゲームオブジェクト
=============================================================================*/
#ifndef SAVE_DATA_TEST_H_
#define	SAVE_DATA_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* セーブデータテスト用ゲームオブジェクト
-------------------------------------*/
class SaveDataTest : public GameObject
{
public:
	SaveDataTest(class Game* game);
	~SaveDataTest(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::SaveDataTest; }

private:
};


#endif //SAVE_DATA_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/