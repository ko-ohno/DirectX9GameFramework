/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshTest.h] メッシュをテストするためのゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッシュをテストするためのゲームオブジェクト
=============================================================================*/
#ifndef MESH_TEST_H_
#define	MESH_TEST_H_

/*--- インクルードファイル ---*/
#include "../GameObject.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* クラス
-------------------------------------*/
class MeshTest : public GameObject
{
public:
	MeshTest(class Game* game);
	~MeshTest(void);

	static MeshTest* Create(class Game* game);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;


private:
	class StdMeshRendererComponent* std_mesh_renderer_component_;

};


#endif //MESH_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/