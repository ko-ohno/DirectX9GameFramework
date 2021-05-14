/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PauseMenu.h] �|�[�Y���j���[��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�|�[�Y���j���[��ʂ̋������`�����N���X
=============================================================================*/
#ifndef PAUSE_MENU_H_
#define	PAUSE_MENU_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �|�[�Y���j���[��ʃN���X
-------------------------------------*/
class PauseMenu : public UI
{
public:
	PauseMenu(class Game* game);
	~PauseMenu(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::PauseMenu; }

private:
};

#endif //PAUSE_MENU_H_
/*=============================================================================
/*		End of File
=============================================================================*/