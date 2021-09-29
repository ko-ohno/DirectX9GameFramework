/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LargeLaser.h] ��^���[�U�[�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F��^���[�U�[�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef LARGE_LASER_H_
#define	LARGE_LASER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Bullet.h"

/*-------------------------------------
/* ��^���[�U�[�Q�[���I�u�W�F�N�g
-------------------------------------*/
class LargeLaser : public Bullet
{
public:
	LargeLaser(class Game* game);
	~LargeLaser(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::LargeLaser; }

	// �p����ݒ�
	void SetOwnerTransfrom(class TransformComponent* transfrom) { owner_transform_ = transfrom; }

private:
	class TransformComponent*		 owner_transform_;

private:
	// ���[�U�[�̃G�t�F�N�g
	class EffectRendererComponent*	 large_laser_;
};


#endif //LARGE_LASER_H_
/*=============================================================================
/*		End of File
=============================================================================*/