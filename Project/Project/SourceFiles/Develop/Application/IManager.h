/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[IManager.h] �Ǘ��N���X�̃C���^�[�t�F�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Ǘ��N���X�̃C���^�[�t�F�[�X�N���X
=============================================================================*/
#ifndef IMANAGER_H_
#define	IMANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "Math.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/*  �Ǘ��N���X�̃C���^�[�t�F�[�X
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

	//�@�p����̃N���X��override�ł���悤��
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