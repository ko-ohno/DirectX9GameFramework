/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DirectionalLight.h] ���s�������C�g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���s�������C�g�N���X
=============================================================================*/
#ifndef DIRECTIONAL_LIGHT_H_
#define	DIRECTIONAL_LIGHT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Light.h"


/*-------------------------------------
/* ���s�������C�g�N���X
-------------------------------------*/
class DirectionalLight : public Light
{
public:
	DirectionalLight(class LightManager* manager);
	~DirectionalLight(void);

private:
	bool Init(void);	//������
	void Uninit(void);	//�I����

public:
	inline void SetLightDirection(float directionX, float directionY, float directionZ) { direction_ = { directionX, directionY, directionZ }; }
	inline void SetLightDirection(D3DXVECTOR3& direction) { direction_ = direction; }
	inline void SetLightDirectionX(float directionX) { direction_.x = directionX; }
	inline void SetLightDirectionY(float directionY) { direction_.x = directionY; }
	inline void SetLightDirectionZ(float directionZ) { direction_.x = directionZ; }

	inline D3DXVECTOR3* SetLightDirection(void) { return &direction_; }

private: 
	//�����x�N�g��
	D3DXVECTOR3	direction_;
};

#endif //DIRECTIONAL_LIGHT_H_
/*=============================================================================
/*		End of File
=============================================================================*/