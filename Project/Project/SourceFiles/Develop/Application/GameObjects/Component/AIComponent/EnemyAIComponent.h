/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyAIComponent.h]  �GAI�̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�GAI�R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef ENEMY_BEHAVIOR_COMPONENT_H_
#define	ENEMY_BEHAVIOR_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../AIComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �GAI�̃R���|�[�l���g
-------------------------------------*/
class EnemyAIComponent : public AIComponent
{
public:
	EnemyAIComponent(class GameObject* owner, int updateOrder = 100);
	~EnemyAIComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::EnemyAIComponent; };


private:
};

#endif //ENEMY_BEHAVIOR_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/