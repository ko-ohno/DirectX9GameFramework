/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Application.h] メインの実行処理
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メインの実行処理
=============================================================================*/
#ifndef APPLICATION_H_
#define	APPLICATION_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* メインの実行処理クラス
-------------------------------------*/
class Application
{
public:
	Application(void);
	~Application(void);

public:
	bool StartUp(const HINSTANCE& hinstance, const int& nCmdShow);
	void Run(void);
	void ShutDown(void);

private:
	bool Init(void);
	void Uninit(void);

private:
	class ApplicationManager* app_manager_;

	std::string				window_title_;
	class Win32APIWindow*	app_window_;
	class DX9Graphics*		dx9_graphics_;
};


#endif //APPLICATION_H_
/*=============================================================================
/*		End of File
=============================================================================*/