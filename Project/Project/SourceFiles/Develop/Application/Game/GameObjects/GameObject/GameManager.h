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

private:
	// �T�C�Y�̊�̃M�Y�����쐬
	class GridGizmoRendererComponent* grid_gizmo_;

	// �v���C���[�̗V�я������
	class BoxGizmoRendererComponent*  player_sandbox_gizmo_;

	// �F���̃`���̕\��
	class EffectRendererComponent*	  effect_space_dust_;

	// BGM�̍Đ�
	class AudioComponent*			  bgm_;

private:
	class IntParameterComponent*	  progress_param_;
	int								  progress_value_;

	class IntParameterComponent*	  score_param_;
	int								  score_value_;
};

#endif //GAME_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/