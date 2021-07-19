 /*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.h] プレイヤーゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーゲームオブジェクト
=============================================================================*/
#ifndef PLAYER_H_
#define	PLAYER_H_

/*--- インクルードファイル ---*/
#include "../Actor.h"

/*-------------------------------------
/* プレイヤーのゲームオブジェクト
-------------------------------------*/
class Player : public Actor
{
public:
	Player(class Game* game);
	~Player(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	// 移動コンポーネント
	class PlayerMoveComponent*		  player_move_;

	//
	// 描画コンポーネント
	//

	class EffectRendererComponent*    effect_after_burner_;

	// レティクル

	class BillboardRendererComponent* far_reticle_;
	class BillboardRendererComponent* near_reticle_;
	class BillboardRendererComponent* lockon_reticle_;
	
	// 武器コンポーネント

	class BlasterWeaponComponent*	  left_blaster_;
	class BlasterWeaponComponent*	  right_blaster_;

	// ロックオン用衝突判定コンポーネント

	class OBBColliderComponent*		  lockon_collider_;
	class BoxGizmoRendererComponent*  lockon_gizmo_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/