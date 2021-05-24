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

	// �F���̒n���̕\��
	class EffectRendererComponent*	  effect_space_dust_;
};

#endif //GAME_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/