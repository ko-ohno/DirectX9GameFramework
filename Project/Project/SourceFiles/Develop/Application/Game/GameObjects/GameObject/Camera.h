/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Camera.h] �J�����̃Q�[���I�u�W�F�N�g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����̃Q�[���I�u�W�F�N�g�̃x�[�X�N���X
=============================================================================*/
#ifndef CAMERA_H_
#define	CAMERA_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "../GameObject.h"
#include "../../../Math.h"

/*-------------------------------------------
/* �J�����̃Q�[���I�u�W�F�N�g�̃x�[�X�N���X
-------------------------------------------*/
class Camera : public GameObject
{
public:
	Camera(class Game* game);
	~Camera(void);

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

	virtual TypeID GetType(void) const { return TypeID::Camera; }

protected:
	class Game* game_;

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