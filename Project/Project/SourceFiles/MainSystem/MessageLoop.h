/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MessageLoop.h] メッセージループクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メッセージループクラス
=============================================================================*/
#ifndef MESSAGE_LOOP_H_
#define	MESSAGE_LOOP_H_

/*--- インクルードファイル ---*/
#include "Win32APIWindow.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/
enum class MessageLoopType
{
	None = -1
	, SplashScreenWindow
	, ApplicationWindow
	, Max
};

/*-------------------------------------
/* メッセージループクラス
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

	//シャットダウンをするか
	bool IsShutDown(void);

private:
	bool IsLoopBreak(void);	//ループを抜けるか

private:
	class IManager* i_manager_;
};

#endif //MESSAGE_LOOP_H_
/*=============================================================================
/*		End of File
=============================================================================*/