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

	// 描画コンポーネント
	class EffectRendererComponent*    effect_after_burner_;

	// 遠くのレティクル
	class BillboardRendererComponent* far_reticle_;

	// 手前のレティクル
	class BillboardRendererComponent* near_reticle_;

	// ロックオンのレティクル
	class BillboardRendererComponent* lockon_reticle_;
	
	// 武器コンポーネント
	class BlasterComponent*			  left_blaster_;
	class BlasterComponent*			  right_blaster_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/