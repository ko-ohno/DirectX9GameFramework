/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.h] 音声テスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：音声テスト用ゲームオブジェクト
=============================================================================*/
#ifndef AUDIO_TEST_H_
#define	AUDIO_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* 音声テスト用ゲームオブジェクト
-------------------------------------*/
class AudioTest : public GameObject
{
public:
	AudioTest(class Game* game);
	~AudioTest(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::AudioTest; }

private:
	class AudioComponent* audio_component_;
	class AudioComponent* audio_component_a_;
};


#endif //AUDIO_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/