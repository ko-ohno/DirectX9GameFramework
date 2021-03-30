/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.h] プレイヤーのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーのゲームオブジェクトクラス定義
=============================================================================*/
#ifndef PLAYER_H_
#define	PLAYER_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* プレイヤーのゲームオブジェクトクラス
-------------------------------------*/
class Player : public GameObject
{
public:
	Player(class Game* game);
	~Player(void);

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	class SpriteRendererComponent* sprite_;
};

#endif //PLAYER_H_
/*=============================================================================
/*		End of File
=============================================================================*/