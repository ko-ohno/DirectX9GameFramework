/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[OBBColliderComponent.h] OBB�R���C�_�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FOBB�R���C�_�R���|�[�l���g
=============================================================================*/
#ifndef OBB_COLLIDER_COMPONENT_H_
#define	OBB_COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ColliderComponent.h"

/*-------------------------------------
/* OBB�R���C�_�R���|�[�l���g�N���X
-------------------------------------*/
class OBBColliderComponent : public ColliderComponent
{
public:
	enum class AxisType
	{
		NONE = -1
		, X
		, Y
		, Z
		, Max
	};

public:
	static constexpr int MAX_AXIS_ELEMENT = static_cast<int>(AxisType::Max);
	Vector3 position_;
	Vector3	axis_element_[MAX_AXIS_ELEMENT];
	float	axis_length_[MAX_AXIS_ELEMENT];

public:
	OBBColliderComponent(class GameObject* owner, int updateOrder = 100);
	~OBBColliderComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::OBBColliderComponent; };

	Vector3* GetPosition(void) { return &position_; }
	void	 SetPosition(Vector3& position) { position_ = position; }
	void	 SetPosition(D3DXVECTOR3& position) { position_ = position; }

	Vector3* GetDirElement(AxisType axisType) { return &axis_element_[(int)axisType]; }

	void SetDirElement(D3DXMATRIX& element)
	{
		memcpy(&axis_element_[(int)AxisType::X], element.m[0], sizeof(D3DXVECTOR3));
		memcpy(&axis_element_[(int)AxisType::Y], element.m[1], sizeof(D3DXVECTOR3));
		memcpy(&axis_element_[(int)AxisType::Z], element.m[2], sizeof(D3DXVECTOR3));
	}

	void SetDirElement(D3DXVECTOR3& axisElement, AxisType axisType)
	{
		axis_element_[(int)axisType].x_ = axisElement.x;
		axis_element_[(int)axisType].y_ = axisElement.y;
		axis_element_[(int)axisType].z_ = axisElement.z;
	}

	void SetDirElement(Vector3& axisElement, AxisType axisType)
	{
		axis_element_[(int)axisType] = axisElement;
	}

	void	 SetDirLength(float axisLength, AxisType axisType) { axis_length_[(int)axisType] = axisLength; }
	float	 GetDirLength(AxisType axisType) { return axis_length_[(int)axisType]; }

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	static float LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3 = 0)
	{
		// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
		// ������Sep�͕W��������Ă��邱��
		float r1 = fabs(D3DXVec3Dot(Sep, e1));
		float r2 = fabs(D3DXVec3Dot(Sep, e2));
		float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
		return r1 + r2 + r3;
	}
};

#endif //OBB_COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/