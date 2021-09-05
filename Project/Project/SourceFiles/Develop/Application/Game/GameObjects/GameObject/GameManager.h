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
	class IntParameterComponent*	  progress_param_;
	int								  progress_value_;

	class IntParameterComponent*	  score_param_;
	int								  score_value_;
};

#endif //GAME_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/