/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemieManager.h] �G�l�~�[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�l�~�[�Ǘ��N���X
=============================================================================*/
#ifndef ENEMIE_MANAGER_H_
#define	ENEMIE_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* �G�l�~�[�Ǘ��N���X
-------------------------------------*/
class EnemieManager
{
public:
	EnemieManager(class Game* game);
	~EnemieManager(void);

	static EnemieManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);	 //������
	void Uninit(void);	 //�I����

public:
	//
	// �G�l�~�[�̒ǉ��ƍ폜
	//

	void AddEnemyGameObjectAddress(class Enemy* enemy);
	void RemoveEnemyGameObjectAddress(class Enemy* enemy);

	// ��������
	class Enemy* FindEnemyGameObjectAddress(class Enemy* enemy);

	const std::vector<class Enemy*>& GetEnemyGameObjectList(void) const { return enemy_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// �}�l�[�W���[�̏��L��
	class Game* game_;

	// �A�N�^�[�̃R���e�i
	std::vector<class Enemy*> enemy_list_;
};

#endif //ENEMIE_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/