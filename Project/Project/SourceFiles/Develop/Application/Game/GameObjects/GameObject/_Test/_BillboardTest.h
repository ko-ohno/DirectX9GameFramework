/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardTest.h] �r���{�[�h�e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�r���{�[�h�e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BILLBOARD_TEST_H_
#define	BILLBOARD_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* �r���{�[�h�e�X�g�p�Q�[���I�u�W�F�N�g
-------------------------------------*/
class BillboardTest : public GameObject
{
public:
	BillboardTest(class Game* game);
	~BillboardTest(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::BillboardTest; }

private:
	class BillboardRendererComponent* billboard_;
	class BillboardRendererComponent* billboard_a_;
};


#endif //BILLBOARD_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/