/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Bullet.h] �o���b�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�o���b�g�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BULLET_H_
#define	BULLET_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../SandBox.h"

/*-------------------------------------
/* �o���b�g�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Bullet : public SandBox
{
public:
	Bullet(class Game* game);
	~Bullet(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	// GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	// �������W�̐ݒ�
	void SetCreatePosition(float posX, float posY, float posZ) { transform_component_->SetTranslation(posX, posY, posZ); }

	// �������W�̐ݒ�
	void SetCreatePosition(const D3DXVECTOR3& position) { transform_component_->SetTranslation(position); }

	// �ړ����x�̐ݒ�
	void SetMoveSpeed(float moveSpeed) { move_speed_ = moveSpeed; }

	// ���g�����ł����鎞�Ԃ̐ݒ�
	void SetKillTimer(float killTimer) { kill_timer_ = killTimer; }

private:
	class FFPMeshRendererComponent*		bullet_mesh_;
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	D3DXVECTOR3 parent_front_vector_;
	D3DXVECTOR3 front_vector_;
	float		kill_timer_;
	float		alive_time_;
	float		move_speed_;
};

#endif //BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/