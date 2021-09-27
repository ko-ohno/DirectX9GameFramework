/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.h] �{�X�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �{�X�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BOSS_H_
#define	BOSS_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Boss : public Enemy
{
public:
	Boss(class Game* game);
	~Boss(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Boss; }

	// �l�R���|�[�l���g�̍X�V
	void UpdateParameter(float deltaTime);

	// �����e�̍X�V
	void UpdateBlaster(float deltaTime, enum class EnemyState enemyState, enum class EnemyMotionState motionState);

	// ���[�U�[�C�̍X�V
	void UpdateLaserCannon(enum class EnemyState enemyState, enum class EnemyMotionState motionState);

	// �Փ˔���̍X�V
	void UpdateCollision(float deltaTime);

private:
	// �Փ˔���̍����A�I�t�Z�b�g���W
	static constexpr float COLLIDER_OFFSET_HEIGHT_POS = 3.f;

private:
	static constexpr float ATTACK_VALUE_BODY_PRESS		= 10.f;
	static constexpr float ATTACK_VALUE_SHOOT			=  5.f;
	static constexpr float ATTACK_VALUE_LASER_CANNON	= 10.f;

	// ���g�̃X�e�[�g���
	enum class EnemyState				enemy_state_old_;
	enum class EnemyMotionState			motion_state_old_;

	//
	// �G�t�F�N�g�R���|�[�l���g
	//
	class EffectRendererComponent*		effect_enemy_action_shoot_;
	class EffectRendererComponent*		effect_player_attack_hit_;

	//
	// �����R���|�[�l���g
	//

	class AudioComponent*				enemy_damage_sound_effect_;

	//
	// �l�R���|�[�l���g
	//

	// �v���C���[�̍ő�HP�̒l�R���|�[�l���g
	class FloatParameterComponent*		max_hp_param_;
	//int								max_hp_value_;	//Actor�N���X�Őݒ�ς�

	// �v���C���[��HP�̒l�R���|�[�l���g
	class FloatParameterComponent*		hp_param_;
	//int								hp_value_;		//Actor�N���X�Őݒ�ς�

private:

	// �ő啐�퐔
	static constexpr int				MAX_WEAPON_COUNT = 3;

	// ����̔��˗p
	bool								is_fire_;
	int									blaster_index_;
	float								switch_time_;
	
	class EnemyBlasterWeaponComponent* enemy_blaster_[MAX_WEAPON_COUNT];
	class LaserCannonWeaponComponent*  laser_cannon_;
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/