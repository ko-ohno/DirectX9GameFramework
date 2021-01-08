/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Result.h] ���U���g��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���U���g��ʂ̋������`�����N���X
=============================================================================*/
#ifndef RESULT_H_
#define	RESULT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UIObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* ���U���g��ʃN���X
-------------------------------------*/
class Result : public UIObject
{
public:
	Result(class GameManager* gameManager);
	~Result(void);

	void Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void Draw(void) override;

	virtual TypeID GetType(void) const { return TypeID::Result; }

private:

};


#endif //RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/