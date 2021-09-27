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

	// 値コンポーネントの更新
	void UpdateParameter(float deltaTime);

	// 光線銃の更新
	void UpdateBlaster(float deltaTime, enum class EnemyState enemyState, enum class EnemyMotionState motionState);

	// レーザー砲の更新
	void UpdateLaserCannon(enum class EnemyState enemyState, enum class EnemyMotionState motionState);

	// 衝突判定の更新
	void UpdateCollision(float deltaTime);

private:
	// 衝突判定の高さ、オフセット座標
	static constexpr float COLLIDER_OFFSET_HEIGHT_POS = 3.f;

private:
	static constexpr float ATTACK_VALUE_BODY_PRESS		= 10.f;
	static constexpr float ATTACK_VALUE_SHOOT			=  5.f;
	static constexpr float ATTACK_VALUE_LASER_CANNON	= 10.f;

	// 自身のステート情報
	enum class EnemyState				enemy_state_old_;
	enum class EnemyMotionState			motion_state_old_;

	//
	// エフェクトコンポーネント
	//
	class EffectRendererComponent*		effect_enemy_action_shoot_;
	class EffectRendererComponent*		effect_player_attack_hit_;

	//
	// 音声コンポーネント
	//

	class AudioComponent*				enemy_damage_sound_effect_;

	//
	// 値コンポーネント
	//

	// プレイヤーの最大HPの値コンポーネント
	class FloatParameterComponent*		max_hp_param_;
	//int								max_hp_value_;	//Actorクラスで設定済み

	// プレイヤーのHPの値コンポーネント
	class FloatParameterComponent*		hp_param_;
	//int								hp_value_;		//Actorクラスで設定済み

private:

	// 最大武器数
	static constexpr int				MAX_WEAPON_COUNT = 3;

	// 武器の発射用
	bool								is_fire_;
	int									blaster_index_;
	float								switch_time_;
	
	class EnemyBlasterWeaponComponent* enemy_blaster_[MAX_WEAPON_COUNT];
	class LaserCannonWeaponComponent*  laser_cannon_;
};

#endif //BOSS_H_
/*=============================================================================
/*		End of File
=============================================================================*/