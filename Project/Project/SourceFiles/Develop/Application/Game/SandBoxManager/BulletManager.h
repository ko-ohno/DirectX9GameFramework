/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BulletManager.h] �A�N�^�[�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�N�^�[�Ǘ��N���X
=============================================================================*/
#ifndef BULLET_MANAGER_H_
#define	BULLET_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* �o���b�g�Ǘ��N���X
-------------------------------------*/
class BulletManager
{
public:
	BulletManager(class Game* game);
	~BulletManager(void);

	static BulletManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);	 //������
	void Uninit(void);	 //�I����

public:
	//
	// �o���b�g�̒ǉ��ƍ폜�ƌ���
	//

	void AddBulletGameObjectAddress(class Bullet* bullet);
	void RemoveBulletGameObjectAddress(class Bullet* bullet);
	class Bullet* FindBulletGameObjectAddress(class Bullet* bullet);

	const std::vector<class Bullet*>& GetBulletGameObjectList(void) const { return bullet_list_; }

	class Game* GetGame(void) { return game_; }

private:
	// �}�l�[�W���[�̏��L��
	class Game* game_;

	// �o���b�g�̃R���e�i
	std::vector<class Bullet*> bullet_list_;
};

#endif //BULLET_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/