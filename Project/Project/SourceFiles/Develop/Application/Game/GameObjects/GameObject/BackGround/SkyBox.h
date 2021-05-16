/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SkyBox.h] スカイボックス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スカイボックス
=============================================================================*/
#ifndef SKY_BOX_H_
#define	SKY_BOX_H_

/*--- インクルードファイル ---*/
#include "../BackGround.h"

/*-------------------------------------
/* スカイボックス
-------------------------------------*/
class SkyBox : public BackGround
{
public:
	SkyBox(class Game* game);
	~SkyBox(void);

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	//GameObjectの関数overrideして、自身の挙動として定義する
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::SkyBox; }

private:
	class StdMeshRendererComponent* mesh_component_;
};

#endif //SkyBox_H_
/*=============================================================================
/*		End of File
=============================================================================*/