/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ParameterComponent.h]  値コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：値コンポーネント
=============================================================================*/
#ifndef PARAMETER_COMPONENT_H_
#define	PARAMETER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"

/*-------------------------------------
/* 値のタイプ
-------------------------------------*/
enum class ParameterType
{
	None = -1
	, HP			// 体力
	, Attack		// 攻撃
	, Deffence		// 防御
	, Progress		// 進行度
	, Score			// スコア
	, Max
};

/*-------------------------------------
/* 値コンポーネント
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

	// 値の型
	ParameterType GetParameterType() const { return parameter_type_; };
	void SetParameterType(ParameterType parameter) { parameter_type_ = parameter; };

	// Intの設定
	int GetInt(void) { return static_cast<int>(value_); }
	void SetInt(int value) { value_ = static_cast<double>(value); }

	// floatの設定
	float GetFloat(void) { return static_cast<float>(value_); }
	void SetFloat(float value) { value_ = static_cast<double>(value); }

	// boolの設定
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
	// パラメータの種類
	ParameterType	parameter_type_;

	// 値
	double value_;
};

#endif //PARAMETER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/