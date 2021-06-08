/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Boss.h] ボスゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： ボスゲームオブジェクト
=============================================================================*/
#ifndef BOSS_H_
#define	BOSS_H_

/*--- インクルードファイル ---*/
#include "../Enemy.h"

/*-------------------------------------
/*  ボス
-------------------------------------*/
enum class BossState
{
	None = -1
	, Enter
	, BodyPress
	, Shooting
	, LaserCannone
	, Max
};

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class Boss : public Enemy
{
public:
	Boss(class Game* game);
	~Boss(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Boss; }

	//
	// ボスの行動ステートの設定
	//

	BossState GetState(void) { return boss_state_; }
	void SetState(BossState bossState) { boss_state_ = bossState; }

private:
	BossState boss_state_;
	class BossAIComponent* boss_ai_;
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/