/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LargeLaser.h] ��^���[�U�[�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F��^���[�U�[�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef LARGE_LASER_H_
#define	LARGE_LASER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../SandBox.h"

/*-------------------------------------
/* ��^���[�U�[�Q�[���I�u�W�F�N�g
-------------------------------------*/
class LargeLaser : public SandBox
{
public:
	LargeLaser(class Game* game);
	~LargeLaser(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
};


#endif //LARGE_LASER_H_
/*=============================================================================
/*		End of File
=============================================================================*/