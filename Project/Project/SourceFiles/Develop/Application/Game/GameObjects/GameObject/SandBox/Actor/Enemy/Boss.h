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

private:
	class BossAIComponent* boss_ai_;
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/