/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[PauseMenu.h] �|�[�Y���j���[��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�|�[�Y���j���[��ʂ̋������`�����N���X
=============================================================================*/
#ifndef PAUSE_MENU_H_
#define	PAUSE_MENU_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �|�[�Y���j���[��ԃX�e�[�g
-------------------------------------*/
enum class PauseMenuSelectState
{
	None = -1
	, Resume
	, Quit

	, Max
};

/*-------------------------------------
/* �|�[�Y���j���[��ʃN���X
-------------------------------------*/
class PauseMenu : public UI
{
public:
	PauseMenu(class Game* game);
	~PauseMenu(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::PauseMenu; }

	void UpdatePauseMenu(float deltaTime);
	void UpdatePauseMenuState(float deltaTime);

private:
	// �|�[�Y�̕\��
	class SpriteRendererComponent* pause_;

	// �Q�[���ɖ߂�
	class SpriteRendererComponent* menu_game_resume_;

	// �Q�[�����I������
	class SpriteRendererComponent* menu_game_quit_;

	// �J�[�\��
	class SpriteRendererComponent* menu_cursor_;

	// ����
	class SpriteRendererComponent* go_next_;

	// �w�i
	class SpriteRendererComponent* menu_bg_;

	// �I����
	class AudioComponent* se_select_;

	// �|�[�Y���j���[�̏��
	PauseMenuSelectState pause_select_state_;
	PauseMenuSelectState pause_select_state_old_;
};

#endif //PAUSE_MENU_H_
/*=============================================================================
/*		End of File
=============================================================================*/