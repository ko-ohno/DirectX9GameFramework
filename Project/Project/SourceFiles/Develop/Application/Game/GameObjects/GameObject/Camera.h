/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Camera.h] �J�����N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����N���X
=============================================================================*/
#ifndef CAMERA_H_
#define	CAMERA_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "../GameObject.h"
#include "../../../Math.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �J�����N���X
-------------------------------------*/
class Camera : public GameObject
{
public:
	Camera(class Game* game);
	~Camera(void);

	static Camera* Create(class Game* game);

	bool Init(void);
	void Uninit(void);

	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	//�ʒu���̎擾

	//�s��֌W
	D3DXMATRIX* GetViewMatrix(void);		
	D3DXMATRIX* GetViewInverseMatrix(void);
	D3DXMATRIX* GetProjection2DMatrix(void);
	D3DXMATRIX* GetProjection3DMatrix(void);

	bool IsGetCameraMoved(void) const;
	void IsSetCameraMoved(bool isCameraMoved);

	virtual TypeID GetType(void) const { return TypeID::Camera; }

private:
	class CameraComponent* camera_component_;

	//�J��������������
	bool is_moved_;

	D3DXVECTOR3 position_
			  , old_position_;
};


#endif //CAMERA_H_
/*=============================================================================
/*		End of File
=============================================================================*/