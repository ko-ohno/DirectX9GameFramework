/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.h] ���[�h��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���[�h��ʃN���X
=============================================================================*/
#ifndef LOADING_SCREEN_H_
#define	LOADING_SCREEN_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* ���[�h��ʃN���X
-------------------------------------*/
class LoadingScreen : public UI
{
public:
	LoadingScreen(class Game* game);
	~LoadingScreen(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
};


#endif //HOGE_H_
/*=============================================================================
/*		End of File
=============================================================================*/