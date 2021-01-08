/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[UIObject.h] UI�I�u�W�F�N�g�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���̃N���X����p���E�h��������UI�I�u�W�F�N�g���쐬����
=============================================================================*/
#ifndef UI_OBJECT_H_
#define	UI_OBJECT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* UI�I�u�W�F�N�g�̃x�[�X�N���X
-------------------------------------*/
class UIObject
{
public:
	enum class TypeID
	{
		None = -1
		//�������g
		, UIObject

		//UIObject
		, HUD
		, PauseMenu
		, Result
		, Title

		, MAX		//UI�I�u�W�F�N�g��ID�̍ő�l
	};

	//�Q�[���I�u�I�u�W�F�N�g�����L����^��ID
	static const char* GameObjectTypeNames[static_cast<int>(TypeID::MAX)];

	enum class State
	{
		None = -1
		, Active	//��������UI�I�u�W�F�N�g���H
		, Closing	//��~����UI�I�u�W�F�N�g���H

		, MAX		//��Ԃ̍ő�l
	};

public:
	UIObject(class GameManager* gameManager);
	virtual ~UIObject(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Input(void);
	virtual void Update(float deltaTime);
	virtual void Draw(void);

	void Close(void) { state_ = State::Closing; }

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::UIObject; } //���override�ł���悤��

protected:
	//UIObject�̏��L��
	class GameManager*				game_manager_;

	//UIObject�̏��
	State							state_;
};

#endif //UI_OBJECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/