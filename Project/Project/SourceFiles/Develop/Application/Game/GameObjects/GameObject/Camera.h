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
#include "../../../Math.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �J�����N���X
-------------------------------------*/
class Camera
{
public:
	Camera(void);
	~Camera(void);

	static Camera* Create(void);

	bool Init(void);
	void Uninit(void);
	void Input(void);
	void Update(float deltaTime);
	void Draw(void);

	void SetAspectSize(class Vector2& aspectSize)
	{
		aspect_size_ = aspectSize;
	}

	D3DXMATRIX GetViewMatrix(void)
	{
		return view_matrix_;
	}

	D3DXMATRIX GetProjectionMatrix(void)
	{
		return projection_matrix_;
	}

private:
	D3DXMATRIX view_matrix_;
	D3DXMATRIX projection_matrix_;
	Vector2	   aspect_size_;


};


#endif //CAMERA_H_
/*=============================================================================
/*		End of File
=============================================================================*/