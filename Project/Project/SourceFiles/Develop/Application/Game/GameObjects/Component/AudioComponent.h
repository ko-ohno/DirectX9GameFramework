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
#include "../../Manager/SoundManager.h"

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

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::AudioComponent; };

	//サウンドの設定
	void SetSound(SoundType soundType);
	
	//サウンドの取得
	class Sound* GetSound(void);

	void Play(void);
	void PlayLoop(void);
	void Stop(void);

	void SetAudioVolume(float volume = 1.f) { audio_volume_ = volume; }
	float GetAudioVolume(void) { return audio_volume_; }

private:
	class Sound*		 sound_;

	float				 audio_volume_;
};


#endif //AUDIO_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/