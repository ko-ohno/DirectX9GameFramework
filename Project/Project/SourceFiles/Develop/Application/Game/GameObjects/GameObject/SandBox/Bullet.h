/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Bullet.h] �o���b�g�̃C���^�[�t�F�[�X�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�o���b�g�̃C���^�[�t�F�[�X�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BULLET_H_
#define	BULLET_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../SandBox.h"

/*-----------------------------------------------------
/* �o���b�g�̃C���^�[�t�F�[�X�Q�[���I�u�W�F�N�g�N���X
-----------------------------------------------------*/
class Bullet : public SandBox
{
public:
	Bullet(class Game* game);
	~Bullet(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::IBullet; }

	// ���̏Փ˔���̎擾
	class SphereColliderComponent*	GetSphereCollider(void) { return sphere_collider_; }

	// OBB�̏Փ˔���̎擾
	class OBBColliderComponent*		GetOBBCollider(void) { return obb_collider_; }

protected:
	// ���̏Փ˔���
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	// OBB�̏Փ˔���
	class OBBColliderComponent*			obb_collider_;
	class BoxGizmoRendererComponent*	obb_collider_gizmo_;
};


#endif //BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/