/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FallowCameraComponent.h]  追従カメラのコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：追従カメラコンポーネントのクラス定義
=============================================================================*/
#ifndef FOLLOW_CAMERA_COMPONENT_H_
#define	FOLLOW_CAMERA_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../CameraComponent.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* 追従カメラのコンポーネント
-------------------------------------*/
class FallowCameraComponent : public CameraComponent
{
public:
	FallowCameraComponent(class GameObject* owner, int updateOrder = 100);
	~FallowCameraComponent(void);

	virtual TypeID GetComponentType() const override { return TypeID::FollowCameraComponent; };


private:
};

#endif //FOLLOW_CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/