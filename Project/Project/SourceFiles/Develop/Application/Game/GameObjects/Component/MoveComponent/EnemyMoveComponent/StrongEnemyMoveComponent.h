/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StrongEnemyMoveComponent.h]  �����G�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����G�̈ړ��R���|�[�l���g
=============================================================================*/
#ifndef BOSS_MOVE_COMPONENT_H_
#define	BOSS_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyMoveComponent.h"


/*-------------------------------------
/* �����G�̈ړ��R���|�[�l���g
-------------------------------------*/
class StrongEnemyMoveComponent : public EnemyMoveComponent
{
public:
	StrongEnemyMoveComponent(class GameObject* owner, int updateOrder = 100);
	~StrongEnemyMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::StrongEnemyMoveComponent; };

private:

	// ���ݍ��W
	D3DXVECTOR3 position_;

	// ��]�p�x
	float yaw_;
	float pitch_;
	float roll_;

	// ���s����
	float execute_time_;
};

#endif //BOSS_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/