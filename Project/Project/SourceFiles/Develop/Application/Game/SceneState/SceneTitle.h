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

	void ChangeScene(void) override;

private:
};


#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/