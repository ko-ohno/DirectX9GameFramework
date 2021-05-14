/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[HUD.h] �Q�[����ʂ�HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ʂ�HUD�̋������`�����N���X
=============================================================================*/
#ifndef HUD_H_
#define	HUD_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �Q�[����ʂ�HUD�N���X
-------------------------------------*/
class HUD : public UI
{
public:
	HUD(class Game* game);
	~HUD(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::HUD; }

private:
};

#endif //HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/