/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SkyBox.h] �X�J�C�{�b�N�X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�J�C�{�b�N�X
=============================================================================*/
#ifndef SKY_BOX_H_
#define	SKY_BOX_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../BackGround.h"

/*-------------------------------------
/* �X�J�C�{�b�N�X
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
	class StdMeshRendererComponent* mesh_component_;
};

#endif //SkyBox_H_
/*=============================================================================
/*		End of File
=============================================================================*/