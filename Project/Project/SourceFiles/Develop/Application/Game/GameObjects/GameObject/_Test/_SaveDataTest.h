/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataTest.h] �Z�[�u�f�[�^�e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Z�[�u�f�[�^�e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef SAVE_DATA_TEST_H_
#define	SAVE_DATA_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* �Z�[�u�f�[�^�e�X�g�p�Q�[���I�u�W�F�N�g
-------------------------------------*/
class SaveDataTest : public GameObject
{
public:
	SaveDataTest(class Game* game);
	~SaveDataTest(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::SaveDataTest; }

private:
};


#endif //SAVE_DATA_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/