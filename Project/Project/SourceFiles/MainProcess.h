/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MainProcess.h] メインの実行処理
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：メインの実行処理
=============================================================================*/
#ifndef MAIN_PROCESS_H_
#define	MAIN_PROCESS_H_

/*--- インクルードファイル ---*/

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* メインの実行処理クラス
-------------------------------------*/
class MainProcess
{
public:
	MainProcess(void);
	~MainProcess(void);

public:
	bool StartUp(void);
	void Run(void);
	void ShutDown(void);

private:
	bool Init(void);
	void Uninit(void);
	void Input(void);
	void Update(float deltaTime);
	void GenerateOutput(void);

private:
	class Manager* manager_;
};


#endif //MAIN_PROCESS_H_
/*=============================================================================
/*		End of File
=============================================================================*/