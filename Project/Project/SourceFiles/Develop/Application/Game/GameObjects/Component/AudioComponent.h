/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioComponent.h] �����R���|�[�l���g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����R���|�[�l���g�̋��L�̃N���X��`
=============================================================================*/
#ifndef AUDIO_COMPONENT_H_
#define	AUDIO_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"
#include "../../Manager/SoundManager.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �����R���|�[�l���g�̃x�[�X�N���X
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

	//�T�E���h�̐ݒ�
	void SetSound(SoundType soundType);
	
	//�T�E���h�̎擾
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