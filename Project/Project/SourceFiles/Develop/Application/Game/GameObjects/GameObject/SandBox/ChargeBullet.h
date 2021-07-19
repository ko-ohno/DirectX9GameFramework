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

	void UpdateChargeBullet(float deltaTime);
	void UpdateChargeBulletState(ChargeBulletState chargeBulletState);

private:
	static constexpr int MAX_CHARGE_BULLET_STATE = static_cast<int>(ChargeBulletState::Max);

	// �o���b�g�̏������L�q
	class SphereColliderComponent* sphere_collider_;
	class SphereGizmoRendererComponent* sphere_collider_gizmo_;

	// ���ꂼ��̃G�t�F�N�g�ԍ��̓o�^��
	enum class EffectType effect_type_[MAX_CHARGE_BULLET_STATE];

	// ���ꂼ��̃G�t�F�N�g�̔z��
	class EffectRendererComponent* effect_[MAX_CHARGE_BULLET_STATE];	

	// �`���[�W�e�̃X�e�[�g
	ChargeBulletState charge_bullet_state_;
	ChargeBulletState charge_bullet_state_old_;
};

#endif //CHARGE_BULLET_H_
/*=============================================================================
/*		End of File
=============================================================================*/