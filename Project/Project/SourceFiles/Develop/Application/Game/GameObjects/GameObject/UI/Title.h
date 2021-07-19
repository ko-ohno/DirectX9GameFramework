/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Title.h] タイトル画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：タイトル画面の挙動を定義したクラス
=============================================================================*/
#ifndef TITLE_H_
#define	TITLE_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
// タイトルメニューの状態
-------------------------------------*/
enum class TitleMenuState
{
	None = -1
	, GameStart
	, GameQuit
	, Max
};

/*-------------------------------------
/* タイトル画面クラス
-------------------------------------*/
class Title : public UI
{
public:
	Title(class Game* game);
	~Title(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Title; } 

	void UpdateTitleSprite(float deltaTime);
	void UpdateBackground(float deltaTime);
	void UpdateMenu(float deltaTime);

private:

	// ゲームを開始する
	class SpriteRendererComponent* menu_game_start_;

	// ゲームを終了する
	class SpriteRendererComponent* menu_game_quit_;

	// カーソル
	class SpriteRendererComponent* menu_cursor_;

	// 説明
	class SpriteRendererComponent* go_next_;

	// タイトル
	class SpriteRendererComponent* title_;

	// 背景
	class SpriteRendererComponent* bg_;

	// 選択音
	class AudioComponent*		   bgm_title_;

	// 選択音
	class AudioComponent*		   se_select_;

	// タイトルメニューの状態ステート
	TitleMenuState select_state_;
	TitleMenuState select_state_old_;

	// 画面サイズ　
	float screen_width_;
	float screen_height_;
};

#endif //TITLE_H_
/*=============================================================================
/*		End of File
=============================================================================*/