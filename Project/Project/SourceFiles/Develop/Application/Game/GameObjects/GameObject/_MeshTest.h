/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshTest.h] ���b�V�����e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�V�����e�X�g���邽�߂̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef MESH_TEST_H_
#define	MESH_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �N���X
-------------------------------------*/
class MeshTest : public GameObject
{
public:
	MeshTest(class Game* game);
	~MeshTest(void);

	static MeshTest* Create(class Game* game);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;


private:

};


#endif //MESH_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/