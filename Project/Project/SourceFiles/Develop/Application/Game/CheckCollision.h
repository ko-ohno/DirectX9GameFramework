/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CheckCollision.h] �Փ˔���̊֐��Q
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Փ˔���̊֐��Q
=============================================================================*/
#ifndef CHECK_COLLISION_H_
#define	CHECK_COLLISION_H_

/*--- �C���N���[�h�t�@�C�� ---*/


// 2D�̏Փ˔���
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/RectangleColliderComponent.h"

// 3D�̏Փ˔���
#include "GameObjects/Component/ColliderComponent/SphereColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/OBBColliderComponent.h"


/*-------------------------------------
/* �Փ˔���̊֐��Q
-------------------------------------*/
namespace CheckCollision
{
	static D3DXVECTOR3 directx_vec3;

	// DirectX�̌`���ɕϊ�
	D3DXVECTOR3* ConvertDirectXVec3(Vector3* vec3);

	//
	// 2D�̏Փ˔���
	//

	// �~�ǂ����̏Փ˔���
	bool CircleVSCircle(class CircleColliderComponent* circleA, class CircleColliderComponent* circleB);

	// ��`�ǂ����̏Փ˔���
	bool RectangleVSRectangle(class RectangleColliderComponent* rectA, class RectangleColliderComponent* rectB);

	//
	// 3D�̏Փ˔���
	//

	// ���ǂ����̏Փ˔���
	bool SphereVSSpghre(class SphereColliderComponent* sphereA, class SphereColliderComponent* sphereB);

	// Obb�ǂ����̏Փ˔���
	bool ObbVSObb(class OBBColliderComponent* obbA, class OBBColliderComponent* obbB);
};

#endif //CHECK_COLLISION_H_
/*=============================================================================
/*		End of File
=============================================================================*/