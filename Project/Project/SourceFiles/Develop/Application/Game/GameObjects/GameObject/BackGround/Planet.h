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
	// �l�R���|�[�l���g�擾�p�Q�[���}�l�[�W���[�ւ̃|�C���^
	class GameObject*					game_manager_;

private:
	class BillboardRendererComponent*	planet_billboard_;

	// �f���̍ő�̑傫��
	static constexpr float MAX_PLANET_SCALE = 99;

	// �f���̑傫��
	float planet_scale_;

	// �f���̍ő�̑傫��
	static constexpr float MAX_PLANET_OFFSET_HEIGHT = -30;

	// �f���̃I�t�Z�b�g���W�̍���
	float planet_offset_height_;

	// �Q�[���̐i�s�x
	int game_progress_value_;
};

#endif //PLANET_H_
/*=============================================================================
/*		End of File
=============================================================================*/