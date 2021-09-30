/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossHUD.h] �{�X��HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X��HUD�N���X
=============================================================================*/
#ifndef BOSS_HUD_H_
#define	BOSS_HUD_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/*�@�{�X��HUD�N���X
-------------------------------------*/
class BossHUD : public UI
{
public:
	BossHUD(class Game* game);
	~BossHUD(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::BossHUD; }

	// HUD�̒l���X�V
	void UpdateHUDValue(float deltaTime);

	// �̗�
	void UpdateHealthBarHUD(float deltaTime);

	// �ˌ��̃A���[�gHUD
	void UpdateWeakPointHUD(float deltaTime);

	// �ˌ��̃A���[�gHUD
	void UpdateAlertShootHUD(float deltaTime);

	// ���僌�[�U�[�Ƒ̓�����U���̃A���[�g��HUD
	void UpdateHorizontalAlertHUD(float deltaTime);

private:
	// �l�R���|�[�l���g�擾�p�Q�[���}�l�[�W���[�ւ̃|�C���^
	class GameObject*				game_manager_;

	// �G�l�~�[�̏��
	enum class EnemyState			boss_state_;
	enum class EnemyState			boss_state_old_;

	// �{�X�̓����̏��
	enum class EnemyMotionState		boss_motion_state_;

	float							delete_time_;

private:
	// �{�X�̗̑̓Q�[�W
	class SpriteRendererComponent*	health_bar_;
	class SpriteRendererComponent*	health_bar_blank_;
	class SpriteRendererComponent*	health_bar_bg_;

	// �{�X�ő�̗̑͒l
	float	max_boss_hp_value_;

	// �{�X�̗̑͒l
	float	boss_hp_value_;

	// ���݂�HP�̊���
	float	boss_hp_rate_;

	// �v���C���[�̗̑͒l
	float	player_hp_value_;

private:
	// �{�X�̎�_�\��
	class BillboardRendererComponent* weak_point_hud_;

	static constexpr float			  MAX_HUD_ANIMATION_TIME_ = 1.f;

	float							  hud_animation_time_;

private:
	//
	//	�{�X�̍U���A���[�g
	//

	static constexpr float			  MAX_ALERT_TIME_ = 2.5f;

	// �A���[�g�𔭐������Ă��邩
	bool							  is_execute_alert_;

	// �A���[�g�𔭐������Ă��邩
	bool							  is_alert_;

	// �A���[�g�̑S�̂̎��s����
	float							  alert_execute_time_;

	// �A���[�g�̋Ǐ��̎��s����
	float							  alert_time_;

	// �r�b�N���}�[�N
	class BillboardRendererComponent* alert_exclamation_;

	// �w�i
	class BillboardRendererComponent* alert_bg_;

	// �A���[�g��SE
	class AudioComponent*			  alert_se_;
	
};


#endif //BOSS_HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/