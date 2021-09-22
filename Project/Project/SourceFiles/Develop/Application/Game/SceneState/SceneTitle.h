/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Scene.h] タイトル場面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：タイトル場面クラス
=============================================================================*/
#ifndef SCENE_TITLE_H_
#define	SCENE_TITLE_H_

/*--- インクルードファイル ---*/
#include "../ISceneState.h"

/*-------------------------------------
/* タイトル場面クラス
-------------------------------------*/
class SceneTitle : public ISceneState
{
public:
	SceneTitle(class Game* game);
	~SceneTitle(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	// BGMの更新処理
	void UpdateBGM(float deltaTime);

	// シーンの切り替え処理
	void ChangeScene(void) override;

private:
	class Title* title_;
};


#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/