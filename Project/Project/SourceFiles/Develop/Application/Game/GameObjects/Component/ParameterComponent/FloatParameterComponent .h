/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FloatParameterComponent.h]  Float�^�l�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FFloat�^�l�R���|�[�l���g
=============================================================================*/
#ifndef INT_PARAMETER_COMPONENT_H_
#define	INT_PARAMETER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ParameterComponent.h"


/*-------------------------------------
/* Float�^�l�R���|�[�l���g
-------------------------------------*/
class FloatParameterComponent  : public ParameterComponent
{
public:
	FloatParameterComponent (class GameObject* owner, int updateOrder = 100);
	~FloatParameterComponent (void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::FloatParameterComponent; };

	// float�̐ݒ�
	float GetFloat(void) { return value_; }
	void SetFloat(float value) { value_ = value; }

private:
	float value_;
};

#endif //INT_PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/