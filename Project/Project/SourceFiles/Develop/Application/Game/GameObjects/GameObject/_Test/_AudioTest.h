/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.h] �����e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef AUDIO_TEST_H_
#define	AUDIO_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* �����e�X�g�p�Q�[���I�u�W�F�N�g
-------------------------------------*/
class AudioTest : public GameObject
{
public:
	AudioTest(class Game* game);
	~AudioTest(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
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