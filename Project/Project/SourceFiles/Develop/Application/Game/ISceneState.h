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
		, parameter_is_fade_execute_(nullptr)
		, parameter_is_scene_changed(nullptr)
		, parameter_is_show_game_screen_(nullptr)
		, is_input_scene_changed_(false)
	{}
	virtual ~ISceneState(void) {}

	virtual bool Init(void)   = 0;
	virtual void Uninit(void) = 0;
	virtual void Input(void)  = 0;
	virtual void Update(float deltaTime) = 0;

	virtual void ChangeScene(void) = 0;

protected:
	class Game*			 game_;

	// �l�R���|�[�l���g�F�t�F�[�h�����s���邩�H
	class ParameterComponent* parameter_is_fade_execute_;

	// �l�R���|�[�l���g�F��ʐ؂�ւ������邩�H
	class ParameterComponent* parameter_is_scene_changed;

	// �l�R���|�[�l���g�F�Q�[����ʂ�\�����邩�H
	class ParameterComponent* parameter_is_show_game_screen_;

	// ��ʂ̐؂�ւ����邩�H
	bool					  is_input_scene_changed_; 
};


#endif //SCENE_STATE_H_
/*=============================================================================
/*		End of File
=============================================================================*/