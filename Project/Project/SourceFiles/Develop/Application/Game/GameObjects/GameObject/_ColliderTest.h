/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.h] �Փ˔���e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef ColliderTest_H_
#define	ColliderTest_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �e�X�g�p�Q�[���I�u�W�F�N�g
-------------------------------------*/
class ColliderTest : public GameObject
{
public:
	ColliderTest(class Game* game);
	~ColliderTest(void);

	static ColliderTest* Create(class Game* game);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
};


#endif //ColliderTest_H_
/*=============================================================================
/*		End of File
=============================================================================*/