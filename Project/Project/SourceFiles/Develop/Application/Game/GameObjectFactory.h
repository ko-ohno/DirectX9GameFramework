/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameObjectFactory.h] �Q�[���I�u�W�F�N�g�̃t�@�N�g���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�u�W�F�N�g�̐����ƍ폜���Ǘ�����N���X
=============================================================================*/
#ifndef GAME_OBJECT_FACTORY_H_
#define	GAME_OBJECT_FACTORY_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"

/*-------------------------------------
/* �Q�[���I�u�W�F�N�g�̃t�@�N�g���N���X
-------------------------------------*/
class GameObjectFactory
{
public:
	GameObjectFactory(class Game* game);
	~GameObjectFactory(void);

	static GameObjectFactory* Create(class Game* game);

	bool StartUp(void);
	void ShutDown(void);

	void Input(void);
	void Update(float deltaTime);

private:
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObjectAll(void);

private:
	std::vector<class GameObject*> game_objects_;
	class Game* game_;

};

#endif //GAME_OBJECT_FACTORY_H_
/*=============================================================================
/*		End of File
=============================================================================*/