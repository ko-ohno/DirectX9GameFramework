/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameManager.h] �Q�[���i�s�Ǘ��I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���i�s�Ǘ��I�u�W�F�N�g
=============================================================================*/
#ifndef GAME_MANAGER_H_
#define	GAME_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �Q�[���i�s�Ǘ��I�u�W�F�N�g
-------------------------------------*/
class GameManager : public GameObject
{
public:
	GameManager(class Game* game);
	~GameManager(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameManager; }

	// �l�R���|�[�l���g�̍X�V����
	void UpdateParameterComponent(float deltaTime);

	// BGM�̍X�V����
	void UpdateBGM(float deltaTime);

private:
	// ��ʐ؂�ւ����s�����H
	bool							  is_secen_change_;

	// �{�X��HUD�𐶐����邩�H
	bool							  is_create_boss_hud_;

private:
	// �G�l�~�[�̃t�@�N�g��
	class EnemyFactory*				  enemy_factory_;

	// �v���C���[�ւ̃|�C���^
	class GameObject*				  player_;

	// �{�X�ւ̃|�C���^
	class GameObject*				  boss_;

private:  
	// �T�C�Y�̊�̃M�Y�����쐬
	class GridGizmoRendererComponent* grid_gizmo_;

	// �v���C���[�̗V�я������
	class BoxGizmoRendererComponent*  player_sandbox_gizmo_;

	// �F���̃`���̕\��
	class EffectRendererComponent*	  effect_space_dust_;

	// BGM�̍Đ�
	class AudioComponent*			  bgm_;

	static constexpr float			  MAX_BGM_VOLUME_ = 0.3f;

	// BGM�̉���
	float							  bgm_volume_;

	// BGM�̃t�F�[�h�A�E�g���s�����H
	bool							  is_bgm_change_;

private:
	// �v���C���[�̍ő�HP�̒l�R���|�[�l���g
	class FloatParameterComponent*	  player_max_hp_param_;
	float							  player_max_hp_value_;

	// �v���C���[��HP�̒l�R���|�[�l���g
	class FloatParameterComponent*	  player_hp_param_;
	float							  player_hp_value_;

	// �Q�[���̐i�s�x�̒l�R���|�[�l���g
	class IntParameterComponent*	  progress_param_;
	int								  progress_value_;

	// �Q�[���X�R�A�̒l�R���|�[�l���g
	class IntParameterComponent*	  score_param_;
	int								  score_value_;

private:
	// �{�X�̍ő�HP�̒l�R���|�[�l���g
	class FloatParameterComponent*	  boss_max_hp_param_;
	float							  boss_max_hp_value_;

	// �{�XHP�̒l�R���|�[�l���g
	class FloatParameterComponent*	  boss_hp_param_;
	float							  boss_hp_value_;

private:
	// �ő吶������
	static constexpr float			  MAX_SPAWN_TIME_  = 99.999f;

	// �����̍�������
	static constexpr float			  SPAWN_DIFF_TIME_ = MAX_SPAWN_TIME_ * 0.166666f; // �ő吶������6����

	// �G�𐶐����邩�H
	bool							  is_enemy_spawn_;

	// ������
	int								  spawn_count_;

	// �Q�[���̎c�莞��
	float							  game_left_time_;  
};

#endif //GAME_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/