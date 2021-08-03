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
#include "../SandBox.h"

/*-------------------------------------
/* ��^���[�U�[�Q�[���I�u�W�F�N�g
-------------------------------------*/
class LargeLaser : public SandBox
{
public:
	LargeLaser(class Game* game);
	~LargeLaser(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	// �p����ݒ�
	void SetTransfrom(class TransformComponent* transfrom) { owner_transform_ = transfrom; }

private:
	class TransformComponent*		 owner_transform_;

private:
	class EffectRendererComponent*	 large_laser_;

	class OBBColliderComponent*		 obb_collider_;
	class BoxGizmoRendererComponent* box_gizmo_;
};


#endif //LARGE_LASER_H_
/*=============================================================================
/*		End of File
=============================================================================*/