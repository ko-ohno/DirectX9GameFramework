/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Result.h] リザルト画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：リザルト画面の挙動を定義したクラス
=============================================================================*/
#ifndef RESULT_H_
#define	RESULT_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* リザルト画面クラス
-------------------------------------*/
enum class ResultMenuState
{
	None = -1
	, Wait
	, GoTitle
	, Max
};

/*-------------------------------------
/* リザルト画面クラス
-------------------------------------*/
class Result : public UI
{
public:
	Result(class Game* game);
	~Result(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Result; }

	void UpdateMenu(float deltaTime);
	void UpdateResultSprite(float deltaTime);
	void UpdateBackground(float deltaTime);
	void UpdateRankingData(float deltaTime);

private:
	static constexpr int MAX_SCORE_DATA = 5;

	// ランキングデータ
	class SpriteRendererComponent*		ranking_bg_[MAX_SCORE_DATA];			// ランキングの背景
	class SpriteRendererComponent*		ranking_double_point_[MAX_SCORE_DATA];	// ダブルコロン
	class SpriteRendererComponent*		ranking_new_[MAX_SCORE_DATA];			// 新しいランキングのデータか？
	class SpriteDigitRendererComponent*	ranking_num_[MAX_SCORE_DATA];			// 順位の数字
	class SpriteDigitRendererComponent* ranking_score_digit_[MAX_SCORE_DATA];	// 点数

	// 説明
	class SpriteRendererComponent* go_next_;

	// タイトル
	class SpriteRendererComponent* result_;

	// 背景
	class SpriteRendererComponent* bg_;

	// BGM
	class AudioComponent*		   bgm_result_;

	// 選択音
	class AudioComponent*		   se_;

	// タイトルメニューの状態ステート
	ResultMenuState result_state_;
	ResultMenuState result_state_old_;

	// 画面サイズ　
	float screen_width_;
	float screen_height_;

private:
	static constexpr float MAX_HUD_ANIMATION_TIME_ = 1.f;
	float hud_animation_time_;
};

#endif //RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/