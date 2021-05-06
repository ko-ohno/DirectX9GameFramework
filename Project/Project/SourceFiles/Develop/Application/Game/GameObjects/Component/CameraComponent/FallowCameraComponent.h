/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FallowCameraComponent.h]  �Ǐ]�J�����̃R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Ǐ]�J�����R���|�[�l���g�̃N���X��`
=============================================================================*/
#ifndef FOLLOW_CAMERA_COMPONENT_H_
#define	FOLLOW_CAMERA_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../CameraComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �Ǐ]�J�����̃R���|�[�l���g
-------------------------------------*/
class FallowCameraComponent : public CameraComponent
{
public:
	FallowCameraComponent(class GameObject* owner, int updateOrder = 100);
	~FallowCameraComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::FollowCameraComponent; };


private:
};

#endif //FOLLOW_CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/