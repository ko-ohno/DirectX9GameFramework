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
	class BillboardRendererComponent*	planet_billboard_;

	// �f����傫������ő�̎���
	static constexpr float MAX_PLANET_SCALE_TIME_ = 99.f;

	// �f���̍ő�̑傫��
	static constexpr float MAX_PLANET_SIZE_		= 150.f;
	static constexpr float DEFAULT_PLANET_SIZE_ =  50.f;

	// ���ݐi�s�`�Řf���ւ̉e������
	float planet_scaling_time_;


	// �f�����I�t�Z�b�g����ő�̎���
	static constexpr float MAX_PLANET_OFFSET_TIME_ = 99.f;

	// �f����Y���W�̍���
	static constexpr float MAX_PLANET_OFFSET_HEIGHT		= -30;
	static constexpr float DEFAULT_PLANET_OFFSET_HEIGHT = -20;

	// �f���̌��݂�Y���W�̍���
	float planet_offset_time_;

};

#endif //PLANET_H_
/*=============================================================================
/*		End of File
=============================================================================*/