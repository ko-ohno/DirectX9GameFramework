/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Scene.h] ゲーム場面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲーム場面クラス
=============================================================================*/
#ifndef SCENE_GAME_H_
#define	SCENE_GAME_H_

/*--- インクルードファイル ---*/
#include "../ISceneState.h"

/*-------------------------------------
/* ゲーム場面クラス
-------------------------------------*/
class SceneGame : public ISceneState
{
public:
	SceneGame(class Game* game);
	~SceneGame(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	// シーンの切り替え処理
	void ChangeScene(void) override;

private:
};

#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/