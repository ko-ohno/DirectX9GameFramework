/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Planet.h] �f���Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f���Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef PLANET_H_
#define	PLANET_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../BackGround.h"

/*-------------------------------------
/* �f���Q�[���I�u�W�F�N�g
-------------------------------------*/
class Planet : public BackGround
{
public:
	Planet(class Game* game);
	~Planet(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Planet; }

private:
};

#endif //PLANET_H_
/*=============================================================================
/*		End of File
=============================================================================*/