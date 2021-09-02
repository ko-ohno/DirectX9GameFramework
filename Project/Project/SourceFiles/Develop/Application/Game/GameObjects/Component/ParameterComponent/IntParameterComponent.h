/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[IntParameterComponent.h]  Int型値コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Int型値コンポーネント
=============================================================================*/
#ifndef INT_PARAMETER_COMPONENT_H_
#define	INT_PARAMETER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ParameterComponent.h"

/*-------------------------------------
/* Int型値コンポーネント
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

	// Intの設定
	int GetInt(void) { return value_; }
	void SetInt(int value) { value_ = value; }

private:
	int value_;
};

#endif //INT_PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/