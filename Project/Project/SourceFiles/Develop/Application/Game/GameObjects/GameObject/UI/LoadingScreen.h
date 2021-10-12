/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Hoge.h] ���[�h��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���[�h��ʃN���X
=============================================================================*/
#ifndef LOADING_SCREEN_H_
#define	LOADING_SCREEN_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �ǂݍ��݃X�e�[�g�N���X
-------------------------------------*/
enum class LoadingState
{
	None = -1
	, Idle
	, FirstHalf
	, SecondHalf
	, SceneChanged

	, Max
};

/*-------------------------------------
/* ���[�h��ʃN���X
-------------------------------------*/
class LoadingScreen : public UI
{
public:
	LoadingScreen(class Game* game);
	~LoadingScreen(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::LoadingScreen; }

	// ���[�h���̃e�L�X�g�̍X�V
	void UpdateLoadingText(float deltaTime);

	//
	// �v���O���X�o�[�̑O���ƌ㔼�̐i���l�̍X�V����
	//

	void UpdateProgressBarFirstHalf(float deltaTime);
	void UpdateProgressBarSecondHalf(float deltaTime);

private:
	// �t�F�[�h�������������H
	class ParameterComponent*	  parameter_is_fade_execute_;

	// �t�F�[�h�������������H
	class ParameterComponent*	  parameter_is_fade_completed_;

private:
	// ��ʐ؂�ւ����s�����H
	class BoolParameterComponent* parameter_is_scene_changed_;

	// �Q�[����ʂ�\�����邩�H
	class BoolParameterComponent* parameter_is_show_game_screen_;

private:
	// ���[�h��ʂ̃X�e�[�g
	enum class LoadingState		  loading_state_;

	// ���[�h��ʂ�\�����邩
	bool						  is_show_loading_screen_;

	// �҂�����
	float						  wait_time_;

	// �e�L�X�g�p�̏��
	int							  text_index_;		// �e�L�X�g�̃C���f�b�N�X
	float						  text_tick_time_;	// �e�L�X�g�p�̃`�b�N����

	// �C���W�P�[�^�[���̏��
	static constexpr float		  MAX_EXECUTE_TIME_	= 4.f;	// �ő���s����
	float						  execute_time_;			// ���s����

	static constexpr float		  MAX_PROGRESS_VALUE_ = 100.f;	// �v���O���X�o�[�̍ő�l
	float						  progress_value_;									// �v���O���X�o�[�̐i��
};


#endif //LOADING_SCREEN_H_
/*=============================================================================
/*		End of File
=============================================================================*/