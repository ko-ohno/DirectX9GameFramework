/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[NormalBullet.h] �ʏ�o���b�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�ʏ�o���b�g�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef NORMAL_BULLET_H_
#define	NORMAL_BULLET_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Bullet.h"

/*-------------------------------------
/* �o���b�g�Q�[���I�u�W�F�N�g
-------------------------------------*/
class NormalBullet : public Bullet
{
public:
	NormalBullet(class Game* game);
	~NormalBullet(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	// GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Bullet; }

	// �v���C���[�̎p��������
	void CombinePlayerTransform(void);

	// �������W�̐ݒ�
	void SetCreatePosition(float posX, float posY, float posZ) { transform_component_->SetTranslation(posX, posY, posZ); }

	// �������W�̐ݒ�
	void SetCreatePosition(const D3DXVECTOR3& position) { transform_component_->SetTranslation(position); }

	// �ړ����x�̐ݒ�
	void SetMoveSpeed(float moveSpeed) { move_speed_ = moveSpeed; }

	// �O�x�N�g����ݒ�
	void SetFrontVector(const D3DXVECTOR3& frontVector)
	{
		is_set_front_vector_ = true;

		front_vector_ = frontVector;
	}

	// ���g�����ł����鎞�Ԃ̐ݒ�
	void SetKillTimer(float killTimer) { kill_timer_ = killTimer; }

private:
	class FFPMeshRendererComponent*		bullet_mesh_;
 
	// �e�ۂ𐶐������t���[����
	bool is_bullet_create_frame_;

	// �O�x�N�g����ݒ肵�Ă��邩�H
	bool is_set_front_vector_;

	D3DXVECTOR3 parent_front_vector_;
	D3DXVECTOR3 right_vector_
			  , up_vector_
			  , front_vector_;
	float		kill_timer_;
	float		alive_time_;
	float		move_speed_;
};

#endif //NORMAL_BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/