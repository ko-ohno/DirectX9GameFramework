/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneState.h] ��ʐ؂�ւ��̃C���^�[�t�F�C�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F��ʐ؂�ւ��̃C���^�[�t�F�C�X�N���X
=============================================================================*/
#ifndef SCENE_STATE_H_
#define	SCENE_STATE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "Game.h"

/*-------------------------------------
/* ��ʐ؂�ւ��̃x�[�X�N���X
-------------------------------------*/
class ISceneState
{
public:
	ISceneState(class Game* game)
		: game_(game)
	{}
	virtual ~ISceneState(void) {}

	virtual bool Init(void)   = 0;
	virtual void Uninit(void) = 0;
	virtual void Input(void)  = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void ChangeScene(void) = 0;

protected:
	class Game* game_;
};


#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/