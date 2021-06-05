/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PlayerMoveComponent.h]  プレイヤーの移動コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：プレイヤーの移動コンポーネント
=============================================================================*/
#ifndef PLAYER_MOVE_COMPONENT_H_
#define	PLAYER_MOVE_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../MoveComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/

/*-------------------------------------
/* プレイヤーの移動コンポーネント
-------------------------------------*/
class PlayerMoveComponent : public MoveComponent
{
public:
	PlayerMoveComponent(class GameObject* owner, int updateOrder = 100);
	~PlayerMoveComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::PlayerMoveComponent; };

	void UpdateMovementState(class Vector2& padThumb);
	//void UpdateMovement(float deltaTime);


private:
	// プレイヤーの遊び場
	class OBBColliderComponent* player_sandbox_;

	//　どこへ移動するか
	bool is_move_top_;
	bool is_move_bottom_;
	bool is_move_left_;
	bool is_move_right_;

	//　移動速度
	float move_speed_;
};

#endif //PLAYER_MOVE_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/