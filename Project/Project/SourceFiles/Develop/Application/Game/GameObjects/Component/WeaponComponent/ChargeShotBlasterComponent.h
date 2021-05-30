/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeShotBlasterComponent.h]  チャージショット光線銃コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：チャージショット光線銃コンポーネント
=============================================================================*/
#ifndef CHARGE_SHOT_BLASTER_COMPONENT_H_
#define	CHARGE_SHOT_BLASTER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../WeaponComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 武器コンポーネント
-------------------------------------*/
class ChargeShotBlasterComponent : public WeaponComponent
{
public:
	ChargeShotBlasterComponent(class GameObject* owner, int updateOrder = 100);
	~ChargeShotBlasterComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::ChargeShotBlasterComponent; };

private:
	// 銃の発射エフェクト
	//class EffectRendererComponent* muzzle_flash_;
};

#endif //CHARGE_SHOT_BLASTER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/