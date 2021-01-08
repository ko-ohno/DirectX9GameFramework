/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[IManager.h] 管理クラスのインターフェースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：管理クラスのインターフェースクラス
=============================================================================*/
#ifndef IMANAGER_H_
#define	IMANAGER_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "Math.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/*  管理クラスのインターフェース
-------------------------------------*/
class IManager
{
public:
	IManager(void){}
	virtual ~IManager(void){}

	virtual bool Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Input(void) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void GenerateOutput(void) = 0;

	//　継承先のクラスでoverrideできるように
	virtual class Vector2* GetSelectedAspectRatio(void) { return NEW Vector2(100.f, 100.f); }
	virtual float GetScreenScaler(void) { return 1.0f; }
	virtual bool IsLoopBreak(void) { return false; }
	virtual bool IsShutDown(void) { return false; }

private:
};


#endif //IMANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/