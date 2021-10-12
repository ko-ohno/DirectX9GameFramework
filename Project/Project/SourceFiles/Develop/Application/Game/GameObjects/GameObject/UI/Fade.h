/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Fade.h] フェードゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：フェードゲームオブジェクト
=============================================================================*/
#ifndef Fade_H_
#define	Fade_H_

/*--- インクルードファイル ---*/
#include "../UI.h"

/*-------------------------------------
/* フェードのステート
-------------------------------------*/
enum class FadeState
{
	None = -1
	, Idle		// 待機
	, FadeOut	// 画面を暗く
	, FadeIn	// 画面を明るく
	, Max
};

/*-------------------------------------
/* フェード画面クラス
-------------------------------------*/
class Fade : public UI
{
public:
	Fade(class Game* game);
	~Fade(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Fade; }

	// フェードの状態を更新
	void UpdateFadeState(void);

	// 画面を暗転
	void FadeOut(float deltaTime);

	// 画面を明転
	void FadeIn(float deltaTime);

private:
	// フェード用のスプライト
	class SpriteRendererComponent* fade_;	

	// 値コンポーネント：フェードを実行するか？
	class BoolParameterComponent*  parameter_is_fade_execute_;

	// 値コンポーネント：フェードを完了したか？
	class BoolParameterComponent*  parameter_is_fade_completed_;

	// フェードの状態
	enum class FadeState		   fade_state_;		

private:
	bool				   is_fade_execute_;
	bool				   is_fade_completed_;

	static constexpr int   MAX_FADE_ALPHA_VALUE_ = 255;
	float				   fade_alpha_;

	static constexpr float MAX_EXECUTE_TIME_ = 1.f;
	float				   execute_time_;
};

#endif //Fade_H_
/*=============================================================================
/*		End of File
=============================================================================*/