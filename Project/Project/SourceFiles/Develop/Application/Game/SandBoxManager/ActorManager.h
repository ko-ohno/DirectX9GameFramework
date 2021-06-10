/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ActorManager.h] �A�N�^�[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�N�^�[�Ǘ��N���X
=============================================================================*/
#ifndef ACTOR_MANAGER_H_
#define	ACTOR_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* �A�N�^�[�Ǘ��N���X
-------------------------------------*/
class ActorManager
{
public:
	ActorManager(class Game* game);
	~ActorManager(void);

	static ActorManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);	 //������
	void Uninit(void);	 //�I����

public:
	//
	// �A�N�^�[�̒ǉ��ƍ폜
	//

	void AddActorGameObjectAddress(class Actor* Actor);
	void RemoveActorGameObjectAddress(class Actor* Actor);

	std::vector<class Actor*> GetActorGameObjectList(void) { return actor_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// �}�l�[�W���[�̏��L��
	class Game* game_;

	// �A�N�^�[�̃R���e�i
	std::vector<class Actor*> actor_list_;
};

#endif //ACTOR_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/