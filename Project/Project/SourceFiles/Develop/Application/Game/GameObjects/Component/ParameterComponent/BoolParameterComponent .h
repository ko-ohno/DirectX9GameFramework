/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BoolParameterComponent.h]  Bool�^�l�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FBool�^�l�R���|�[�l���g
=============================================================================*/
#ifndef BOOL_PARAMETER_COMPONENT_H_
#define	BOOL_PARAMETER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ParameterComponent.h"

/*-------------------------------------
/* Bool�^�l�R���|�[�l���g
-------------------------------------*/
class BoolParameterComponent  : public ParameterComponent
{
public:
	BoolParameterComponent (class GameObject* owner, int updateOrder = 100);
	~BoolParameterComponent (void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BoolParameterComponent; };

	// bool�̐ݒ�
	bool GetBool(void) { return is_value_; }
	void SetBool(bool isValue) { is_value_ = isValue; }

private:
	bool is_value_;
};

#endif //BOOL_PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/