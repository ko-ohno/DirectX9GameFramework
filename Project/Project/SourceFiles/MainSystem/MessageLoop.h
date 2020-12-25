/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MessageLoop.h] ���b�Z�[�W���[�v�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�Z�[�W���[�v�N���X
=============================================================================*/
#ifndef MESSAGE_LOOP_H_
#define	MESSAGE_LOOP_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "Win32APIWindow.h"

/*-------------------------------------
/* �\����
-------------------------------------*/
enum class MessageLoopType
{
	None = -1
	, SplashScreenWindow
	, ApplicationWindow
	, Max
};

/*-------------------------------------
/* ���b�Z�[�W���[�v�N���X
-------------------------------------*/
class MessageLoop
{
public:
	MessageLoop(class IManager* iManager);
	~MessageLoop(void);

	static MessageLoop* Create(MessageLoopType msgLoopTyep, const WindowStyle& windowStyle);

	bool StartUp(void);
	void Run(void);
	void ShutDown(void);


	class Vector2* GetSelectedAspectRatio(void);

	//�V���b�g�_�E�������邩
	bool IsShutDown(void);

private:
	bool IsLoopBreak(void);	//���[�v�𔲂��邩

private:
	class IManager* i_manager_;
};

#endif //MESSAGE_LOOP_H_
/*=============================================================================
/*		End of File
=============================================================================*/