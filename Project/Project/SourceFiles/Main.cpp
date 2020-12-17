/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Main.cpp] メインモジュール
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メインで実行する処理の流れを定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "StdAfx.h"
#include "MainProcess.h"

/*-----------------------------------------------------------------------------
/* メイン処理
-----------------------------------------------------------------------------*/
//ビルドの設定によってコンソール画面を表示するかを決定する

#if defined(_DEBUG) || defined(DEBUG)
int main(void)
{
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
#endif

	//メモリリーク検知用
#if defined(_DEBUG) || defined(DEBUG) //下記の関数はリリースビルド時に実行されないらしいけれど、一応設定しておく
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*----------------------------------------------
	/* メインの実行命令
	----------------------------------------------*/
	{
		MainProcess main_process;

		bool is_success = main_process.StartUp();	//起動処理
		if (is_success)
		{
			main_process.Run();						//実行処理
		}
		main_process.ShutDown();					//停止処理
	}
	return 0;
}

/*=============================================================================
/*		End of File
=============================================================================*/