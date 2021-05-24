/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.h]  �ړ��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�ړ��R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef MOVE_COMPONENT_H_
#define	MOVE_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �ړ��̃R���|�[�l���g
-------------------------------------*/
class MoveComponent : public Component
{
public:
	MoveComponent(class GameObject* owner, int updateOrder);
	~MoveComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::MoveComponent; };

protected:
	class TransformComponent* transform_component_;
};


#endif //MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/