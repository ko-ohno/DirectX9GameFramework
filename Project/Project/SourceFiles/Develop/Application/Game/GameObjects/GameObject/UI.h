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

/*-------------------------------------
/* UI�̏�ԃN���X
-------------------------------------*/
enum class UIState
{
	None = -1
	, Active	//��������UI�I�u�W�F�N�g���H
	, Closing	//��~����UI�I�u�W�F�N�g���H

	, MAX		//��Ԃ̍ő�l
};

/*-------------------------------------
/* UI�̃x�[�X�N���X
-------------------------------------*/
class UI : public GameObject
{
public:
	UI(class Game* game);
	virtual ~UI(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	void Close(void) { state_ = UIState::Closing; }

	void SetState(UIState state) { state_ = state; };
	UIState GetState(void) { return state_; }
	 
	virtual TypeID GetType(void) const { return TypeID::UI; } //���override�ł���悤��

protected:
	//UI�̏��L��
	class Game* game_;

	//UI�̏��
	UIState		state_;
};

#endif //UI_H_
/*=============================================================================
/*		End of File
=============================================================================*/