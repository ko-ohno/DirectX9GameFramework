/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[IntParameterComponent.h]  Int�^�l�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FInt�^�l�R���|�[�l���g
=============================================================================*/
#ifndef INT_PARAMETER_COMPONENT_H_
#define	INT_PARAMETER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ParameterComponent.h"

/*-------------------------------------
/* Int�^�l�R���|�[�l���g
-------------------------------------*/
class IntParameterComponent : public ParameterComponent
{
public:
	IntParameterComponent(class GameObject* owner, int updateOrder = 100);
	~IntParameterComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::IntParameterComponent; };

	// Int�̐ݒ�
	int GetInt(void) { return value_; }
	void SetInt(int value) { value_ = value; }

private:
	int value_;
};

#endif //INT_PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/