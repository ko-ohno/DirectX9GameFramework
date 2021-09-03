/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FloatParameterComponent.h]  Float型値コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Float型値コンポーネント
=============================================================================*/
#ifndef FLOAT_PARAMETER_COMPONENT_H_
#define	FLOAT_PARAMETER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ParameterComponent.h"


/*-------------------------------------
/* Float型値コンポーネント
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

private:
};

#endif //FLOAT_PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/