/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraTest.h] �J�����e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef CAMERA_TEST_H_
#define	CAMERA_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Camera.h"

/*-------------------------------------
/* �J�����e�X�g�p�Q�[���I�u�W�F�N�g
-------------------------------------*/
class CameraTest : public Camera
{
public:
	CameraTest(class Game* game);
	~CameraTest(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::CameraTest; }

private:
};


#endif //CAMERA_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/