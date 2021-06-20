/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Enemy.h] 敵ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明： 敵ゲームオブジェクト
=============================================================================*/
#ifndef ENEMY_H_
#define	ENEMY_H_

/*--- インクルードファイル ---*/
#include "../Actor.h"

/*-------------------------------------
/*  エネミーのステート
-------------------------------------*/
enum class EnemyState
{
	None = -1
	, Wait				// 待機
	, Enter				// 登場
	, Move				// 移動
	, BodyPress			// 体当たり
	, Shooting			// 射撃
	, LaserCannon		// レーザー砲

	, Destroy			// 撃破された状態

	, Max
};

/*-------------------------------------
/*  敵ゲームオブジェクト
-------------------------------------*/
class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	~Enemy(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Enemy; }

	inline EnemyState GetEnemyState(void) { return enemy_state_; }
	inline void SetEnemyState(EnemyState actorState) { enemy_state_ = actorState; }

protected:
	// 敵のステート
	enum class EnemyState	  enemy_state_;

	// 敵のAIコンポーネント
	class EnemyAIComponent*   enemy_ai_;

	// 移動コンポーネント
	class EnemyMoveComponent* enemy_move_;
};

#endif //ENEMY_H_
/*=============================================================================
/*		End of File
=============================================================================*/