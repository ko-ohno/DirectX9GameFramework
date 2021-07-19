/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.h] �{�X�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F �{�X�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef BOSS_H_
#define	BOSS_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  �G�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Boss : public Enemy
{
public:
	Boss(class Game* game);
	~Boss(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Boss; }

private:
	static constexpr float ATTACK_VALUE_BODY_PRESS		= 10.f;
	static constexpr float ATTACK_VALUE_SHOOT			=  5.f;
	static constexpr float ATTACK_VALUE_LASER_CANNON	= 10.f;

	// �ő啐�퐔
	static constexpr int MAX_WEAPON_COUNT = 3;
	
	class BlasterWeaponComponent* blaster_[MAX_WEAPON_COUNT];
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/