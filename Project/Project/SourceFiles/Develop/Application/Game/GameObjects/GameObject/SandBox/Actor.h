/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Actor.h] �A�N�^�[�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�N�^�[�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef ACTOR_H_
#define	ACTOR_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �A�N�^�[�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Actor : public GameObject
{
public:
	Actor(class Game* game);
	virtual ~Actor(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Actor; }

private:
};


#endif //ACTOR_H_
/*=============================================================================
/*		End of File
=============================================================================*/