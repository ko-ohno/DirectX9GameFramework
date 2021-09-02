/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BoolParameterComponent.h]  Bool型値コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：Bool型値コンポーネント
=============================================================================*/
#ifndef BOOL_PARAMETER_COMPONENT_H_
#define	BOOL_PARAMETER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../ParameterComponent.h"

/*-------------------------------------
/* Bool型値コンポーネント
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

	// boolの設定
	bool GetBool(void) { return is_value_; }
	void SetBool(bool isValue) { is_value_ = isValue; }

private:
	bool is_value_;
};

#endif //BOOL_PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/