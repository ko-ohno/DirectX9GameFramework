/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioComponent.h] 音声コンポーネントのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：音声コンポーネントの共有のクラス定義
=============================================================================*/
#ifndef AUDIO_COMPONENT_H_
#define	AUDIO_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 音声コンポーネントのベースクラス
-------------------------------------*/
class AudioComponent : public Component
{
public:
	AudioComponent(class GameObject* owner, int updateOrder = 100);
	~AudioComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

private:

};


#endif //AUDIO_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/