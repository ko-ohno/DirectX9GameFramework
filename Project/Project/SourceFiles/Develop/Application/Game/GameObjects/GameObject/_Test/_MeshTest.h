/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshTest.h] メッシュテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッシュテスト用ゲームオブジェクト
=============================================================================*/
#ifndef MESH_TEST_H_
#define	MESH_TEST_H_

/*--- インクルードファイル ---*/
#include "../../GameObject.h"


/*-------------------------------------
/* メッシュテスト用ゲームオブジェクト
-------------------------------------*/
class MeshTest : public GameObject
{
public:
	MeshTest(class Game* game);
	~MeshTest(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::MeshTest; }

private:
	class StdMeshRendererComponent* std_mesh_renderer_component_;

	class FFPMeshRendererComponent* std_mesh_renderer_component_a;
	class StdMeshRendererComponent* std_mesh_renderer_component_b;
	class StdMeshRendererComponent* std_mesh_renderer_component_c;

};


#endif //MESH_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/