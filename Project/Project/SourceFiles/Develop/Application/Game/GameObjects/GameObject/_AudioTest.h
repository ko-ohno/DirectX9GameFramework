/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.h] ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオブジェクト
=============================================================================*/
#ifndef AUDIO_TEST_H_
#define	AUDIO_TEST_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* クラス
-------------------------------------*/
class AudioTest : public GameObject
{
public:
	AudioTest(class Game* game);
	~AudioTest(void);

	static AudioTest* Create(class Game* game);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class AudioComponent* audio_component_;
};


#endif //AUDIO_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/