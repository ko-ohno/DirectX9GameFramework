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
#include "../UIObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �|�[�Y���j���[��ʃN���X
-------------------------------------*/
class PauseMenu : public UIObject
{
public:
	PauseMenu(class GameManager* gameManager);
	~PauseMenu(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void Draw(void) override;

	virtual TypeID GetType(void) const { return TypeID::PauseMenu; }

private:

};


#endif //PAUSE_MENU_H_
/*=============================================================================
/*		End of File
=============================================================================*/