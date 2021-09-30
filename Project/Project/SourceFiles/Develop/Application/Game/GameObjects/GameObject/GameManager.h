/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameManager.h] ゲーム進行管理オブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム進行管理オブジェクト
=============================================================================*/
#ifndef GAME_MANAGER_H_
#define	GAME_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* ゲーム進行管理オブジェクト
-------------------------------------*/
class GameManager : public GameObject
{
public:
	GameManager(class Game* game);
	~GameManager(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameManager; }

	// 値コンポーネントの更新処理
	void UpdateParameterComponent(float deltaTime);

	// BGMの更新処理
	void UpdateBGM(float deltaTime);

private:
	// 場面切り替えを行うか？
	bool							  is_secen_change_;

	// ボスのHUDを生成するか？
	bool							  is_create_boss_hud_;

private:
	// エネミーのファクトリ
	class EnemyFactory*				  enemy_factory_;

	// プレイヤーへのポインタ
	class GameObject*				  player_;

	// ボスへのポインタ
	class GameObject*				  boss_;

private:  
	// サイズの基準のギズモを作成
	class GridGizmoRendererComponent* grid_gizmo_;

	// プレイヤーの遊び場を可視化
	class BoxGizmoRendererComponent*  player_sandbox_gizmo_;

	// 宇宙のチリの表示
	class EffectRendererComponent*	  effect_space_dust_;

	// BGMの再生
	class AudioComponent*			  bgm_;

	static constexpr float			  MAX_BGM_VOLUME_ = 0.3f;

	// BGMの音量
	float							  bgm_volume_;

	// BGMのフェードアウトを行うか？
	bool							  is_bgm_change_;

private:
	// プレイヤーの最大HPの値コンポーネント
	class FloatParameterComponent*	  player_max_hp_param_;
	float							  player_max_hp_value_;

	// プレイヤーのHPの値コンポーネント
	class FloatParameterComponent*	  player_hp_param_;
	float							  player_hp_value_;

	// ゲームの進行度の値コンポーネント
	class IntParameterComponent*	  progress_param_;
	int								  progress_value_;

	// ゲームスコアの値コンポーネント
	class IntParameterComponent*	  score_param_;
	int								  score_value_;

private:
	// ボスの最大HPの値コンポーネント
	class FloatParameterComponent*	  boss_max_hp_param_;
	float							  boss_max_hp_value_;

	// ボスHPの値コンポーネント
	class FloatParameterComponent*	  boss_hp_param_;
	float							  boss_hp_value_;

private:
	// 最大生成時間
	static constexpr float			  MAX_SPAWN_TIME_  = 99.999f;

	// 生成の差分時間
	static constexpr float			  SPAWN_DIFF_TIME_ = MAX_SPAWN_TIME_ * 0.166666f; // 最大生成時間6等分

	// 敵を生成するか？
	bool							  is_enemy_spawn_;

	// 生成回数
	int								  spawn_count_;

	// ゲームの残り時間
	float							  game_left_time_;  
};

#endif //GAME_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/