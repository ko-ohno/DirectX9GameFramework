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
	class FFPMeshRendererComponent* mesh_space_ship_;

	class FFPMeshRendererComponent* test_mesh_;

	class EffectRendererComponent*  effect_after_burner_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/