/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] �G�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �G�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Actor.h"

/*-------------------------------------
/*  �G�l�~�[�̃X�e�[�g
-------------------------------------*/
enum class EnemyState
{
	None = -1
	, Wait				// �ҋ@
	, Enter				// �o��
	, Move				// �ړ�
	, BodyPress			// �̓�����
	, Shooting			// �ˌ�
	, LaserCannon		// ���[�U�[�C

	, Destroy			// ���j���ꂽ���

	, Max
};

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	~Enemy(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

	inline EnemyState GetEnemyState(void) { return enemy_state_; }
	inline void SetEnemyState(EnemyState actorState) { enemy_state_ = actorState; }

protected:
	// �G�̃X�e�[�g
	enum class EnemyState	  enemy_state_;

	// �G��AI�R���|�[�l���g
	class EnemyAIComponent*   enemy_ai_;

	// �ړ��R���|�[�l���g
	class EnemyMoveComponent* enemy_move_;
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/