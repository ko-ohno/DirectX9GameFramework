/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraComponent.h] カメラのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラコンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef CAMERA_COMPONENT_H_
#define	CAMERA_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* カメラコンポーネントのベースクラス
-------------------------------------*/
class CameraComponent : public Component
{
public:
	CameraComponent(class GameObject* owner, int updateOrder = 100);
	~CameraComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void CallComponent() override;

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; };

private:
protected:
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/