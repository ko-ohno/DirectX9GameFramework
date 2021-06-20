/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderManager.h] �R���C�_�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�R���C�_�Ǘ��N���X
=============================================================================*/
#ifndef COLLIDER_MANAGER_H_
#define	COLLIDER_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* �R���C�_�̎��
-------------------------------------*/
enum class ColliderType
{
	None = -1
	, Circle
	, Rectangle
	, Sphere
	, OBB

	, Max
};

/*-------------------------------------
/* �R���C�_�Ǘ��N���X
-------------------------------------*/
class ColliderManager
{
public:
	static const char* ColliderTypeNames[static_cast<int>(ColliderType::Max)];

public:
	ColliderManager(class Game* game);
	~ColliderManager(void);

	static ColliderManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);	 //������
	void Uninit(void);	 //�I����

public:
	//
	// �R���C�_�̒ǉ��ƍ폜
	//

	void AddColliderComponentAddress(class ColliderComponent* colliderComponent);
	void RemoveColliderComponentAddress(class ColliderComponent* colliderComponent);

	std::vector<class ColliderComponent*>& GetColliderComponentList(void) { return collider_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// �}�l�[�W���[�̏��L��
	class Game* game_;

	// �R���C�_�̃R���e�i
	std::vector<class ColliderComponent*> collider_list_;
};


#endif //COLLIDER_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/