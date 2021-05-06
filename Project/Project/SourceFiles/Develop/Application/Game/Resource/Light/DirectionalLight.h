/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DirectionalLight.h] 平行光源ライトクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：平行光源ライトクラス
=============================================================================*/
#ifndef DIRECTIONAL_LIGHT_H_
#define	DIRECTIONAL_LIGHT_H_

/*--- インクルードファイル ---*/
#include "../Light.h"


/*-------------------------------------
/* 平行光源ライトクラス
-------------------------------------*/
class DirectionalLight : public Light
{
public:
	DirectionalLight(class LightManager* manager);
	~DirectionalLight(void);

private:
	bool Init(void);	//初期化
	void Uninit(void);	//終了化

public:
	inline void SetLightDirection(float directionX, float directionY, float directionZ) { direction_ = { directionX, directionY, directionZ }; }
	inline void SetLightDirection(D3DXVECTOR3& direction) { direction_ = direction; }
	inline void SetLightDirectionX(float directionX) { direction_.x = directionX; }
	inline void SetLightDirectionY(float directionY) { direction_.x = directionY; }
	inline void SetLightDirectionZ(float directionZ) { direction_.x = directionZ; }

	inline D3DXVECTOR3* SetLightDirection(void) { return &direction_; }

private: 
	//向きベクトル
	D3DXVECTOR3	direction_;
};

#endif //DIRECTIONAL_LIGHT_H_
/*=============================================================================
/*		End of File
=============================================================================*/