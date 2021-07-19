/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Title.h] �^�C�g����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�^�C�g����ʂ̋������`�����N���X
=============================================================================*/
#ifndef TITLE_H_
#define	TITLE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
// �^�C�g�����j���[�̏��
-------------------------------------*/
enum class TitleMenuState
{
	None = -1
	, GameStart
	, GameQuit
	, Max
};

/*-------------------------------------
/* �^�C�g����ʃN���X
-------------------------------------*/
class Title : public UI
{
public:
	Title(class Game* game);
	~Title(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Title; } 

	void UpdateTitleSprite(float deltaTime);
	void UpdateBackground(float deltaTime);
	void UpdateMenu(float deltaTime);

private:

	// �Q�[�����J�n����
	class SpriteRendererComponent* menu_game_start_;

	// �Q�[�����I������
	class SpriteRendererComponent* menu_game_quit_;

	// �J�[�\��
	class SpriteRendererComponent* menu_cursor_;

	// ����
	class SpriteRendererComponent* go_next_;

	// �^�C�g��
	class SpriteRendererComponent* title_;

	// �w�i
	class SpriteRendererComponent* bg_;

	// �I����
	class AudioComponent*		   bgm_title_;

	// �I����
	class AudioComponent*		   se_select_;

	// �^�C�g�����j���[�̏�ԃX�e�[�g
	TitleMenuState select_state_;
	TitleMenuState select_state_old_;

	// ��ʃT�C�Y�@
	float screen_width_;
	float screen_height_;
};

#endif //TITLE_H_
/*=============================================================================
/*		End of File
=============================================================================*/