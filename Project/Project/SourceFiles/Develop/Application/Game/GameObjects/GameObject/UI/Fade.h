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
/* フェードゲームオブジェクト
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

private:
	class SpriteRendererComponent* fade_;
};

#endif //Fade_H_
/*=============================================================================
/*		End of File
=============================================================================*/