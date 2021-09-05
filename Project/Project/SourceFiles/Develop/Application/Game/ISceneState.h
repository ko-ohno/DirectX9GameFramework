/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneState.h] 場面切り替えのインターフェイスクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：場面切り替えのインターフェイスクラス
=============================================================================*/
#ifndef SCENE_STATE_H_
#define	SCENE_STATE_H_

/*--- インクルードファイル ---*/
#include "Game.h"

/*-------------------------------------
/* 場面切り替えのベースクラス
-------------------------------------*/
class ISceneState
{
public:
	ISceneState(class Game* game)
		: game_(game)
	{}
	virtual ~ISceneState(void) {}

	virtual bool Init(void)   = 0;
	virtual void Uninit(void) = 0;
	virtual void Input(void)  = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void ChangeScene(void) = 0;

protected:
	class Game* game_;
};


#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/