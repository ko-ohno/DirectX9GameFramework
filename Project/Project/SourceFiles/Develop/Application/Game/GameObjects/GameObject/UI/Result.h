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
#include "../UI.h"

/*-------------------------------------
/* ���U���g��ʃN���X
-------------------------------------*/
class Result : public UI
{
public:
	Result(class Game* game);
	~Result(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Result; }

private:
};

#endif //RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/