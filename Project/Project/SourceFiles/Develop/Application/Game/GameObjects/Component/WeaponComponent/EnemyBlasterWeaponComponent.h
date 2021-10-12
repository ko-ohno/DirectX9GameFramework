/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyBlasterWeaponComponent.h]  コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：コンポーネント
=============================================================================*/
#ifndef ENEMY_BLASTER_WEAPON_COMPONENT_H_
#define	ENEMY_BLASTER_WEAPON_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../WeaponComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 敵の武器コンポーネント
-------------------------------------*/
class EnemyBlasterWeaponComponent : public WeaponComponent
{
public:
	EnemyBlasterWeaponComponent(class GameObject* owner, int updateOrder = 100);
	~EnemyBlasterWeaponComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::EnemyBlasterWeaponComponent; };

	// 敵のターゲットを見つける処理
	class Actor* FindPlayerGameObject(void);

	// 攻撃
	void Fire(void);

protected:
	// 銃の発射エフェクト
	class EffectRendererComponent*		muzzle_flash_;

	// このコンポーネントの位置を示すgizmo
	class SphereGizmoRendererComponent* sphere_gizmo_;
};

#endif //COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/