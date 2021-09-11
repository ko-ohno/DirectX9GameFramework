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
		, parameter_is_fade_execute_(nullptr)
		, parameter_is_scene_changed(nullptr)
		, parameter_is_show_game_screen_(nullptr)
		, is_input_scene_changed_(false)
	{}
	virtual ~ISceneState(void) {}

	virtual bool Init(void)   = 0;
	virtual void Uninit(void) = 0;
	virtual void Input(void)  = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void ChangeScene(void) = 0;

protected:
	class Game*			 game_;

	// 値コンポーネント：フェードを実行するか？
	class ParameterComponent* parameter_is_fade_execute_;

	// 値コンポーネント：場面切り替えをするか？
	class ParameterComponent* parameter_is_scene_changed;

	// 値コンポーネント：ゲーム画面を表示するか？
	class ParameterComponent* parameter_is_show_game_screen_;

	// 場面の切り替えするか？
	bool					  is_input_scene_changed_; 
};


#endif //SCENE_STATE_H_
/*=============================================================================
/*		End of File
=============================================================================*/