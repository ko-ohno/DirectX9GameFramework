/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeaponComponent.h]  武器コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：武器コンポーネント
=============================================================================*/
#ifndef WEAPON_COMPONENT_H_
#define	WEAPON_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"
#include "TransformComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 武器コンポーネント
-------------------------------------*/
class WeaponComponent : public Component
{
public:
	WeaponComponent(class GameObject* owner, int updateOrder = 100);
	~WeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::WeaponComponent; };

	//平行移動成分の操作

	inline void SetTranslation(float posX, float posY, float posZ = 0.f) { position_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetTranslationX(float posX) { position_.x = posX; }
	inline void SetTranslationY(float posY) { position_.y = posY; }
	inline void SetTranslationZ(float posZ) { position_.z = posZ; }

protected:
	class TransformComponent* owner_transform_;

	D3DXVECTOR3 position_;
};

#endif //WEAPON_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/