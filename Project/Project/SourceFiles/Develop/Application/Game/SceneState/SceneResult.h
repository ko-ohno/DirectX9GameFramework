/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneResult.h] リザルト場面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：リザルト場面クラス
=============================================================================*/
#ifndef SCENE_RESULT_H_
#define	SCENE_RESULT_H_

/*--- インクルードファイル ---*/
#include "../ISceneState.h"

/*-------------------------------------
/* リザルト場面クラス
-------------------------------------*/
class SceneResult : public ISceneState
{
public:
	SceneResult(class Game* game);
	~SceneResult(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void ChangeScene(void) override;

private:
};

#endif // SCENE_RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/