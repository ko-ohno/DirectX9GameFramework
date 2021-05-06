/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderTest.h] �Փ˔���e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef COLLIDER_TEST_H_
#define	COLLIDER_TEST_H_

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
	class GridGizmoRendererComponent* grid_gizmo_renderer_component_;

	class BoxGizmoRendererComponent* box_gizmo_renderer_component_;
	class BoxGizmoRendererComponent* box_gizmo_renderer_component_a_;

	class OBBColliderComponent* obb_collider_component_;
	class OBBColliderComponent* obb_collider_component_a_;

	class SphereGizmoRendererComponent* sphere_gizmo_renderer_component_;
	class SphereGizmoRendererComponent* sphere_gizmo_renderer_component_a_;

	class SphereColliderComponent* sphere_collider_component_;
	class SphereColliderComponent* sphere_collider_component_a_;

};


#endif //COLLIDER_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/