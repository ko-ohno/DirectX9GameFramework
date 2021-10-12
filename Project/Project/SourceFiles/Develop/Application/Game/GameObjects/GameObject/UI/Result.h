/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Result.h] ���U���g��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���U���g��ʂ̋������`�����N���X
=============================================================================*/
#ifndef RESULT_H_
#define	RESULT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* ���U���g��ʃN���X
-------------------------------------*/
enum class ResultMenuState
{
	None = -1
	, Wait
	, GoTitle
	, Max
};

/*-------------------------------------
/* ���U���g��ʃN���X
-------------------------------------*/
class Result : public UI
{
public:
	Result(class Game* game);
	~Result(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Result; }

	void UpdateMenu(float deltaTime);
	void UpdateResultSprite(float deltaTime);
	void UpdateBackground(float deltaTime);
	void UpdateRankingData(float deltaTime);

private:
	static constexpr int MAX_SCORE_DATA = 5;

	// �����L���O�f�[�^
	class SpriteRendererComponent*		ranking_bg_[MAX_SCORE_DATA];			// �����L���O�̔w�i
	class SpriteRendererComponent*		ranking_double_point_[MAX_SCORE_DATA];	// �_�u���R����
	class SpriteRendererComponent*		ranking_new_[MAX_SCORE_DATA];			// �V���������L���O�̃f�[�^���H
	class SpriteDigitRendererComponent*	ranking_num_[MAX_SCORE_DATA];			// ���ʂ̐���
	class SpriteDigitRendererComponent* ranking_score_digit_[MAX_SCORE_DATA];	// �_��

	// ����
	class SpriteRendererComponent* go_next_;

	// �^�C�g��
	class SpriteRendererComponent* result_;

	// �w�i
	class SpriteRendererComponent* bg_;

	// BGM
	class AudioComponent*		   bgm_result_;

	// �I����
	class AudioComponent*		   se_;

	// �^�C�g�����j���[�̏�ԃX�e�[�g
	ResultMenuState result_state_;
	ResultMenuState result_state_old_;

	// ��ʃT�C�Y�@
	float screen_width_;
	float screen_height_;

private:
	static constexpr float MAX_HUD_ANIMATION_TIME_ = 1.f;
	float hud_animation_time_;
};

#endif //RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/