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


private:
	// エネミーのファクトリ
	class EnemyFactory*				  enemy_factory_;

	// プレイヤーへのポインタ
	class GameObject*				  player_;

private:  
	// サイズの基準のギズモを作成
	class GridGizmoRendererComponent* grid_gizmo_;

	// プレイヤーの遊び場を可視化
	class BoxGizmoRendererComponent*  player_sandbox_gizmo_;

	// 宇宙のチリの表示
	class EffectRendererComponent*	  effect_space_dust_;

	// BGMの再生
	class AudioComponent*			  bgm_;


private:
	// プレイヤーの最大HPの値コンポーネント
	class IntParameterComponent*	  player_max_hp_param_;
	int								  player_max_hp_value_;

	// プレイヤーのHPの値コンポーネント
	class IntParameterComponent*	  player_hp_param_;
	int								  player_hp_value_;

	// ゲームの進行度の値コンポーネント
	class IntParameterComponent*	  progress_param_;
	int								  progress_value_;

	// ゲームスコアの値コンポーネント
	class IntParameterComponent*	  score_param_;
	int								  score_value_;

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