/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PauseMenu.h] ポーズメニュー画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ポーズメニュー画面の挙動を定義したクラス
=============================================================================*/
#ifndef PAUSE_MENU_H_
#define	PAUSE_MENU_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* ポーズメニュー状態ステート
-------------------------------------*/
enum class PauseMenuSelectState
{
	None = -1
	, Resume
	, Quit

	, Max
};

/*-------------------------------------
/* ポーズメニュー画面クラス
-------------------------------------*/
class PauseMenu : public UI
{
public:
	PauseMenu(class Game* game);
	~PauseMenu(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::PauseMenu; }

	void UpdatePauseMenu(float deltaTime);
	void UpdatePauseMenuState(float deltaTime);

private:
	// ポーズの表題
	class SpriteRendererComponent* pause_;

	// ゲームに戻る
	class SpriteRendererComponent* menu_game_resume_;

	// ゲームを終了する
	class SpriteRendererComponent* menu_game_quit_;

	// カーソル
	class SpriteRendererComponent* menu_cursor_;

	// 説明
	class SpriteRendererComponent* go_next_;

	// 背景
	class SpriteRendererComponent* menu_bg_;

	// 選択音
	class AudioComponent* se_select_;

	// ポーズメニューの状態
	PauseMenuSelectState pause_select_state_;
	PauseMenuSelectState pause_select_state_old_;
};

#endif //PAUSE_MENU_H_
/*=============================================================================
/*		End of File
=============================================================================*/