/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BackGround.h] �w�i�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�w�i�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BACK_GROUND_H_
#define	BACK_GROUND_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �w�i�Q�[���I�u�W�F�N�g
-------------------------------------*/
class BackGround : public GameObject
{
public:
	BackGround(class Game* game);
	virtual ~BackGround(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::BackGround; }

private:
};


#endif //BACK_GROUND_H_
/*=============================================================================
/*		End of File
=============================================================================*/