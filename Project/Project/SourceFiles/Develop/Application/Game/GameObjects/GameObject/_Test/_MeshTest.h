/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshTest.h] ���b�V���e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�V���e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef MESH_TEST_H_
#define	MESH_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../GameObject.h"


/*-------------------------------------
/* ���b�V���e�X�g�p�Q�[���I�u�W�F�N�g
-------------------------------------*/
class MeshTest : public GameObject
{
public:
	MeshTest(class Game* game);
	~MeshTest(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::MeshTest; }

private:
	class StdMeshRendererComponent* std_mesh_renderer_component_;

	class FFPMeshRendererComponent* std_mesh_renderer_component_a;
	class StdMeshRendererComponent* std_mesh_renderer_component_b;
	class StdMeshRendererComponent* std_mesh_renderer_component_c;

};


#endif //MESH_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/