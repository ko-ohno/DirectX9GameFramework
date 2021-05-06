/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EnemyAIComponent.h]  敵AIのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：敵AIコンポーネントのクラス定義
=============================================================================*/
#ifndef ENEMY_BEHAVIOR_COMPONENT_H_
#define	ENEMY_BEHAVIOR_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../AIComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 敵AIのコンポーネント
-------------------------------------*/
class EnemyAIComponent : public AIComponent
{
public:
	EnemyAIComponent(class GameObject* owner, int updateOrder = 100);
	~EnemyAIComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::EnemyAIComponent; };


private:
};

#endif //ENEMY_BEHAVIOR_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/