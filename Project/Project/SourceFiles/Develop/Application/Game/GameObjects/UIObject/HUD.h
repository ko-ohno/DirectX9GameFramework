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
#include "../UIObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �Q�[����ʂ�HUD�N���X
-------------------------------------*/
class HUD : public UIObject
{
public:
	HUD(class GameManager* gameManager);
	~HUD(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void Draw(void) override;

	virtual TypeID GetType(void) const { return TypeID::HUD; }

private:

};


#endif //HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/