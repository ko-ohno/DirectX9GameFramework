/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameOver.h] ゲームオーバー画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームオーバー画面クラス
=============================================================================*/
#ifndef GAME_OVER_H_
#define	GAME_OVER_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* ゲームオーバー画面クラス
-------------------------------------*/
class GameOver : public UI
{
public:
	GameOver(class Game* game);
	~GameOver(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameOver; }

private:
	// ポーズの表題
	class SpriteRendererComponent* game_over_;

	// ゲームオーバー画面の半透明な背景
	class SpriteRendererComponent* bg_;

	// 次へ進むのテキスト表示
	class SpriteRendererComponent* text_go_to_next_;

private:
	static constexpr float		   MAX_SCREEN_ANIMATION_TIME_ = 1.f;

	float						   screen_animation_time_;
};

#endif //GAME_OVER_H_
/*=============================================================================
/*		End of File
=============================================================================*/