/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BlasterComponent.h]  光線銃コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：光線銃コンポーネント
=============================================================================*/
#ifndef BLASTER_COMPONENT_H_
#define	BLASTER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../WeaponComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 武器コンポーネント
-------------------------------------*/
class BlasterComponent : public WeaponComponent
{
public:
	BlasterComponent(class GameObject* owner, int updateOrder = 100);
	~BlasterComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::BlasterComponent; };

	void Fire(void);

private:
	// 銃の発射エフェクト
	class EffectRendererComponent* muzzle_flash_;
};

#endif //WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/