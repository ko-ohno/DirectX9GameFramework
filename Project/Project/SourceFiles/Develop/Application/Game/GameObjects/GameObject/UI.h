/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[UI.h] UI�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���̃N���X����p���E�h��������UI�I�u�W�F�N�g���쐬����
=============================================================================*/
#ifndef UI_H_
#define	UI_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "../GameObject.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* UI�̃x�[�X�N���X
-------------------------------------*/
class UI : public GameObject
{
public:
	enum class State
	{
		None = -1
		, Active	//��������UI�I�u�W�F�N�g���H
		, Closing	//��~����UI�I�u�W�F�N�g���H

		, MAX		//��Ԃ̍ő�l
	};

public:
	UI(class Game* game);
	virtual ~UI(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Input(void);
	virtual void Update(float deltaTime);

	void Close(void) { state_ = State::Closing; }

	void SetState(State state) { state_ = state; };
	State GetState(void) { return state_; }

	virtual TypeID GetType(void) const { return TypeID::UI; } //���override�ł���悤��

protected:
	//UIObject�̏��L��
	class Game* game_;

	//UI�̏��
	State		state_;
};

#endif //UI_H_
/*=============================================================================
/*		End of File
=============================================================================*/