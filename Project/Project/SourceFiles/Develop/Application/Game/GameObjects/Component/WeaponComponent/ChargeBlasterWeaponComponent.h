/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBlasterWeaponComponent.h]  �����e����R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����e����R���|�[�l���g
=============================================================================*/
#ifndef CHARGE_BLASTER_WEAPON_COMPONENT_H_
#define	CHARGE_BLASTER_WEAPON_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../WeaponComponent.h"
#include "../../GameObject/SandBox/Bullet/ChargeBullet.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �����e����R���|�[�l���g
-------------------------------------*/
class ChargeBlasterWeaponComponent : public WeaponComponent
{
public:
	ChargeBlasterWeaponComponent(class GameObject* owner, int updateOrder = 100);
	~ChargeBlasterWeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BlasterComponent; };

	// �`���[�W�e�̍쐬
	void CreateChargeBullet(void);

	// �`���[�W�e�̔���
	void Fire(void);

	// ���b�N�I���̕W�I���X�V
	void UpdateLockonTarget(float deltaTime);

	// �`���[�W�e�̃C���X�^���X���m�F
	bool IsCheckChargeBulletInstance(void);

	// �`���[�W�e�̏�Ԃ̐ݒ�
	ChargeBulletState GetChargeBulletState(void);
	void SetChargeBulletState(ChargeBulletState chargeBulletState);

private:
	bool								is_bullet_created_;
	bool								is_fire_;

private: 
	// �W�I�ւ̃|�C���^
	class Enemy*						target_enemy_;

	// ���b�N�I�����L���ɂȂ��Ă��邩�H
	bool								is_enable_lockon_;

	// ���݂̃��b�N�I���̏�Ԃ����������܂ł̍ő厞��
	static constexpr float				MAX_LOCKON_RELEASE_TIME_ = 2.f;

	// ���݂̃��b�N�I���̏�Ԃ����������܂ł̌��ݎ���
	float								lockon_release_time_;

	// ���b�N�I���̍ő�A�j���[�V��������
	static constexpr float				MAX_LOCKON_RETICLE_ANIMATION_TIME_ = 0.5f;

	// ���b�N�I���̌��݂̃A�j���[�V��������
	float								lockon_reticle_animation_time_;

	// ���b�N�I����HUD�̍ő�A�j���[�V��������
	static constexpr float				MAX_LOCKON_RETICLE_HUD_ANIMATION_TIME_ = 1.f;

	// ���b�N�I����HUD�̌��݂̃A�j���[�V��������
	float								lockon_reticle_hud_animation_time_;

	// ���b�N�I���̃��e�B�N���̍��W
	D3DXVECTOR3							lockon_reticle_src_pos_;
	D3DXVECTOR3							lockon_reticle_dst_pos_;

private:
	// �`���[�W�e�ւ̃|�C���^
	class ChargeBullet*					charge_bullet_;

protected:
	// �e�̔��˃G�t�F�N�g
	class EffectRendererComponent*		muzzle_flash_;

	// ���b�N�I���̃��e�B�N��
	class BillboardRendererComponent*	lockon_reticle_;

	// ���b�N�I���̃��e�B�N���F���L�҂̎p���̉e�����󂯂Ă���
	class BillboardRendererComponent*   lockon_reticle_owner_transform_order_;

	// ���b�N�I���̌x����
	class AudioComponent*				lockon_alert_se_;

	// ���b�N�I���p�Փ˔���R���|�[�l���g
	class OBBColliderComponent*			lockon_collider_;
	class BoxGizmoRendererComponent*	lockon_gizmo_;

	// ���̃R���|�[�l���g�̈ʒu������gizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //BLASTER_WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/