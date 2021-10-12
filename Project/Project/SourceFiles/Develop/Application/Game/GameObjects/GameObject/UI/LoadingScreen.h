/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.h] ロード画面クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ロード画面クラス
=============================================================================*/
#ifndef LOADING_SCREEN_H_
#define	LOADING_SCREEN_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* 読み込みステートクラス
-------------------------------------*/
enum class LoadingState
{
	None = -1
	, Idle
	, FirstHalf
	, SecondHalf
	, SceneChanged

	, Max
};

/*-------------------------------------
/* ロード画面クラス
-------------------------------------*/
class LoadingScreen : public UI
{
public:
	LoadingScreen(class Game* game);
	~LoadingScreen(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::LoadingScreen; }

	// ロード中のテキストの更新
	void UpdateLoadingText(float deltaTime);

	//
	// プログレスバーの前半と後半の進捗値の更新処理
	//

	void UpdateProgressBarFirstHalf(float deltaTime);
	void UpdateProgressBarSecondHalf(float deltaTime);

private:
	// フェードが完了したか？
	class ParameterComponent*	  parameter_is_fade_execute_;

	// フェードが完了したか？
	class ParameterComponent*	  parameter_is_fade_completed_;

private:
	// 場面切り替えを行うか？
	class BoolParameterComponent* parameter_is_scene_changed_;

	// ゲーム画面を表示するか？
	class BoolParameterComponent* parameter_is_show_game_screen_;

private:
	// ロード画面のステート
	enum class LoadingState		  loading_state_;

	// ロード画面を表示するか
	bool						  is_show_loading_screen_;

	// 待ち時間
	float						  wait_time_;

	// テキスト用の情報
	int							  text_index_;		// テキストのインデックス
	float						  text_tick_time_;	// テキスト用のチック時間

	// インジケーター側の情報
	static constexpr float		  MAX_EXECUTE_TIME_	= 4.f;	// 最大実行時間
	float						  execute_time_;			// 実行時間

	static constexpr float		  MAX_PROGRESS_VALUE_ = 100.f;	// プログレスバーの最大値
	float						  progress_value_;									// プログレスバーの進捗
};


#endif //LOADING_SCREEN_H_
/*=============================================================================
/*		End of File
=============================================================================*/