/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ApplicationManager.h] アプリ全体の処理の管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：全体の処理の管理クラス
=============================================================================*/
#ifndef APPLICATION_MANAGER_H_
#define	APPLICATION_MANAGER_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* 構造体
-------------------------------------*/




/*-------------------------------------
/* アプリ全体の処理の管理クラス
-------------------------------------*/
class ApplicationManager
{
private:
	ApplicationManager(void);

public:
	~ApplicationManager(void);

	static ApplicationManager* Create(void);

	static bool Init(void);
	static void Uninit(void);
	static void Input(void);
	static void Update(float deltaTime);
	static void GenerateOutput(void);

private:
};

#endif //APPLICATION_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/