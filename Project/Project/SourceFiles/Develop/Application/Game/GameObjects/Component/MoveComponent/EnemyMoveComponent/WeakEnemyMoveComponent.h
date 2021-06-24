/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemyMoveComponent.h]  �{�X�̈ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X�̈ړ��R���|�[�l���g
=============================================================================*/
#ifndef WEAK_ENEMY_MOVE_COMPONENT_H_
#define	WEAK_ENEMY_MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../EnemyMoveComponent.h"

/*-------------------------------------
/* �ア�G�̈ړ��R���|�[�l���g
-------------------------------------*/
class WeakEnemyMoveComponent : public EnemyMoveComponent
{
public:
	WeakEnemyMoveComponent(class GameObject* owner, int updateOrder = 100);
	~WeakEnemyMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::WeakEnemyMoveComponent; };

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