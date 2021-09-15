/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyFactoryState.h] �G�l�~�[�t�@�N�g���̏�ԃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�t�@�N�g���̏�ԃN���X
=============================================================================*/
#ifndef ENEMY_FACTORY_STATE_H_
#define	ENEMY_FACTORY_STATE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "GameObjects/GameObject/SandBox/Actor/Enemy/Boss.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy/StrongEnemy.h"
#include "GameObjects/GameObject/SandBox/Actor/Enemy/WeakEnemy.h"

/*-------------------------------------
/* �G�l�~�[�t�@�N�g���̏�ԃN���X
-------------------------------------*/
class EnemyFactoryState
{
public:
	EnemyFactoryState(class Game* game)
		: game_(game)
		, execute_time_(0.f)
		, is_spawn(false)
		, spawn_count(0)
	{}
	virtual ~EnemyFactoryState(void) {}

	virtual bool Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(float deltaTime) = 0;

protected:
	class Game* game_;

	// �e�X�e�[�g�̍ő吶����
	static constexpr int	MAX_SPAWN_COUNT_ = 10;

	// �ő吶�����̔����̐�
	static constexpr int	HALF_SPAWN_COUNT_ = static_cast<int>(MAX_SPAWN_COUNT_ * 0.5f);

	// �����̍�������
	static constexpr float	SPAWN_DIFF_TIME_ = 1.0f;
	
	// ���s����
	float execute_time_;

	// �������邩�H
	bool is_spawn;

	// �����������H
	int  spawn_count;
};


#endif //ENEMY_FACTORY_STATE_H_
/*=============================================================================
/*		End of File
=============================================================================*/