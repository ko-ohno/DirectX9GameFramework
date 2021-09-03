/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ParameterComponent.h]  �l�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�l�R���|�[�l���g
=============================================================================*/
#ifndef PARAMETER_COMPONENT_H_
#define	PARAMETER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*-------------------------------------
/* �l�̃^�C�v
-------------------------------------*/
enum class ParameterType
{
	None = -1
	, HP			// �̗�
	, Attack		// �U��
	, Deffence		// �h��
	, Progress		// �i�s�x
	, Score			// �X�R�A
	, Max
};

/*-------------------------------------
/* �l�R���|�[�l���g
-------------------------------------*/
class ParameterComponent : public Component
{
public:
	ParameterComponent(class GameObject* owner, int updateOrder = 100);
	~ParameterComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::ParameterComponent; };

	// �l�̌^
	ParameterType GetParameterType() const { return parameter_type_; };
	void SetParameterType(ParameterType parameter) { parameter_type_ = parameter; };

	// Int�̐ݒ�
	int GetInt(void) { return static_cast<int>(value_); }
	void SetInt(int value) { value_ = static_cast<double>(value); }

	// float�̐ݒ�
	float GetFloat(void) { return static_cast<float>(value_); }
	void SetFloat(float value) { value_ = static_cast<double>(value); }

	// bool�̐ݒ�
	bool GetBool(void)
	{
		if (value_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void SetBool(bool isValue) { value_ = static_cast<double>(isValue); }

protected:
	// �p�����[�^�̎��
	ParameterType	parameter_type_;

	// �l
	double value_;
};

#endif //PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/