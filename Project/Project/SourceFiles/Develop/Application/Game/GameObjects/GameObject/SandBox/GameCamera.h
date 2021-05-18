/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameCamera.h] �Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef GameCamera_H_
#define	GameCamera_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Camera.h"

/*-------------------------------------
/* �N���X
-------------------------------------*/
class GameCamera : public Camera
{
public:
	GameCamera(class Game* game);
	~GameCamera(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameCamera; }

private:
};


#endif //GameCamera_H_
/*=============================================================================
/*		End of File
=============================================================================*/