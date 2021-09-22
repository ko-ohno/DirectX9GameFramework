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

	// �̗�
	void UpdateHealthBarHUD(float deltaTime);

	// �ˌ��̃A���[�gHUD
	void UpdateAlertShootHUD(float deltaTime);

	// ���僌�[�U�[�Ƒ̓�����U���̃A���[�g��HUD
	void UpdateHorizontalAlertHUD(float deltaTime);

private:
	// �l�R���|�[�l���g�擾�p�Q�[���}�l�[�W���[�ւ̃|�C���^
	class GameObject*				game_manager_;

	// �{�X�ւ̃|�C���^
	class Enemy*					boss_;

	// �G�l�~�[�̏��
	enum class EnemyState			boss_state_;

private:
	// �{�X�̗̑̓Q�[�W
	class SpriteRendererComponent*	health_bar_;
	class SpriteRendererComponent*	health_bar_blank_;
	class SpriteRendererComponent*	health_bar_bg_;

	// �ő�̗̑͒l
	float	max_hp_value_;

	// �̗͒l
	float	hp_value_;

	// ���݂�HP�̊���
	float	hp_rate_;

private:
	// �{�X�̎�_�\��
	class BillboardRendererComponent* weak_point_;

private:
	//
	//	�{�X�̍U���A���[�g
	//

	static constexpr float			  MAX_ALERT_TIME = 3.f;

	// �A���[�g�����s���邩
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