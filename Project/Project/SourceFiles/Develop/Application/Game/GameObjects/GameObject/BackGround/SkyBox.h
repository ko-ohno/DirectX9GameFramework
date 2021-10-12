/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SkyBox.h] �X�J�C�{�b�N�X�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�J�C�{�b�N�X�̃Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef SKY_BOX_H_
#define	SKY_BOX_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../BackGround.h"

/*-------------------------------------
/* �X�J�C�{�b�N�X�̃Q�[���I�u�W�F�N�g
-------------------------------------*/
class SkyBox : public BackGround
{
public:
	SkyBox(class Game* game);
	~SkyBox(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::SkyBox; }

private:
	class FFPMeshRendererComponent* ffp_mesh_sky_box_;
};

#endif //SkyBox_H_
/*=============================================================================
/*		End of File
=============================================================================*/