/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardTest.h] �r���{�[�h���e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�r���{�[�h���e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BILLBOARD_TEST_H_
#define	BILLBOARD_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �N���X
-------------------------------------*/
class BillboardTest : public GameObject
{
public:
	BillboardTest(class Game* game);
	~BillboardTest(void);

	static BillboardTest* Create(class Game* game);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class BillboardRendererComponent* billboard_;
	class BillboardRendererComponent* billboard_a_;
};


#endif //BILLBOARD_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/