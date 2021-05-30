/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SandBox.h] �Q�[�����\������Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[�����\������Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef SAND_BOX_H_
#define	SAND_BOX_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GameObject.h"

/*-------------------------------------
/* �Q�[�����\������Q�[���I�u�W�F�N�g
-------------------------------------*/
class SandBox : public GameObject
{
public:
	SandBox(class Game* game);
	~SandBox(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Actor; }

protected:
	class MoveComponent* move_component_;
};


#endif //SandBox_H_
/*=============================================================================
/*		End of File
=============================================================================*/