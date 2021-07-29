/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.h] �`���[�W�e�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�`���[�W�e�̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef CHARGE_BULLET_H_
#define	CHARGE_BULLET_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../SandBox.h"

/*-------------------------------------
/* �`���[�W�e�̃X�e�[�g
-------------------------------------*/
enum class ChargeBulletState
{
	None = -1
	, Charge
	, Hold
	, Fire
	, Bullet
	, Explosion
	, Idle
	, End

	, Max
};

/*-------------------------------------
/* �`���[�W�e�̃Q�[���I�u�W�F�N�g
-------------------------------------*/
class ChargeBullet : public SandBox
{
public:
	ChargeBullet(class Game* game);
	~ChargeBullet(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::ChargeBullet; }

	// �`���[�W�e�̔���
	void Fire(void);

private:
	void UpdateMovement(float deltaTime);
	void UpdateChargeBulletState(float deltaTime);
	void UpdateParticleEffect(void);

	void UpdateParticleEffectPlayState(ChargeBulletState chargeBulletState);
	void UpdateColilision(ChargeBulletState chargeBulletState);

public:

	void SetWorldMatrix(D3DXMATRIX& worldMatrix)
	{
		transform_component_->SetRotationMatrix(worldMatrix);
		transform_component_->SetTranslation(worldMatrix._41, worldMatrix._42, worldMatrix._43);
	}

	// �������W�̐ݒ�
	void SetTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }

	// �ړ����x�̐ݒ�
	void SetMoveSpeed(float moveSpeed) { move_speed_ = moveSpeed; }

	// ���g�����ł����鎞�Ԃ̐ݒ�
	void SetKillTimer(float killTimer) { kill_timer_ = killTimer; }

	// ���b�N�I�����Ă��邩
	void IsSetLockon(bool isLockon) { is_lockon_ = isLockon; }

public:
	// �`���[�W�e�̏�Ԃ̐ݒ�
	ChargeBulletState GetChargeBulletState(void) { return charge_bullet_state_; }
	void SetChargeBulletState(ChargeBulletState chargeBulletState) { charge_bullet_state_ = chargeBulletState; }

private:
	// �`���[�W�e�̍ő�X�e�[�g��
	static constexpr int MAX_CHARGE_BULLET_STATE = 5;

	// ���ꂼ��̃G�t�F�N�g�ԍ��̓o�^��
	enum class EffectType effect_type_[MAX_CHARGE_BULLET_STATE];

	// ���ꂼ��̃G�t�F�N�g�̔z��
	class EffectRendererComponent* effect_[MAX_CHARGE_BULLET_STATE];	

	// �Փ˔���
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	// �`���[�W�e�̃X�e�[�g
	ChargeBulletState charge_bullet_state_;
	ChargeBulletState charge_bullet_state_old_;

	bool		is_fire_;		// ���˂��Ă��邩
	bool		is_hit_;		// �q�b�g���Ă��邩
	bool		is_lockon_;		// ���b�N�I�������Ă��邩�H
	bool		is_next_state_;	// ���̃X�e�[�g�ւ����ނ��H

	D3DXVECTOR3 parent_front_vector_;	// �e�I�u�W�F�N�g�̎p���̑O�x�N�g��
	float		move_speed_;			// �ړ����x

	// ���W
	D3DXVECTOR3 position_;

	// ��Ԃ̍��W
	D3DXVECTOR3 src_position_
			  , dst_position_;

	float		lerp_execute_time_;		// ��Ԃ̎��s����
	float		kill_timer_;			// ���ł܂ł̐�������
	float		alive_time_;			// ��������
	float		state_time_;			// �X�e�[�g�̎��s����

};

#endif //CHARGE_BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/