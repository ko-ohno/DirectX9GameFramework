/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameClear.h] �Q�[���N���A��ʃQ�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���N���A��ʃQ�[���I�u�W�F�N�g
=============================================================================*/
#ifndef GAME_CLEAR_H_
#define	GAME_CLEAR_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �Q�[���N���A��ʃN���X
-------------------------------------*/
class GameClear : public UI
{
public:
	GameClear(class Game* game);
	~GameClear(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameClear; }

private:
	// �|�[�Y�̕\��
	class SpriteRendererComponent* game_clear_;

	// �Q�[���I�[�o�[��ʂ̔������Ȕw�i
	class SpriteRendererComponent* bg_;

	// ���֐i�ނ̃e�L�X�g�\��
	class SpriteRendererComponent* text_go_to_next_;

private:
	static constexpr float		   MAX_SCREEN_ANIMATION_TIME_ = 1.f;

	float						   screen_animation_time_;
};

#endif //GAME_CLEAR_H_
/*=============================================================================
/*		End of File
=============================================================================*/