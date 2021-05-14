/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Title.h] �^�C�g����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�^�C�g����ʂ̋������`�����N���X
=============================================================================*/
#ifndef TITLE_H_
#define	TITLE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �^�C�g����ʃN���X
-------------------------------------*/
class Title : public UI
{
public:
	Title(class Game* game);
	~Title(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Title; } 

private:
};

#endif //TITLE_H_
/*=============================================================================
/*		End of File
=============================================================================*/