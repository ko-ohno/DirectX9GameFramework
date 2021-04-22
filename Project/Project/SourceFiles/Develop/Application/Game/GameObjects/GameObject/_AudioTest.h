/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AudioTest.h] �Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef AUDIO_TEST_H_
#define	AUDIO_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �N���X
-------------------------------------*/
class AudioTest : public GameObject
{
public:
	AudioTest(class Game* game);
	~AudioTest(void);

	static AudioTest* Create(class Game* game);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class AudioComponent* audio_component_;
};


#endif //AUDIO_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/