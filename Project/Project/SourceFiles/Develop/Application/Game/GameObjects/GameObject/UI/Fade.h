/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Fade.h] �t�F�[�h�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�t�F�[�h�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef Fade_H_
#define	Fade_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �t�F�[�h�̃X�e�[�g
-------------------------------------*/
enum class FadeState
{
	None = -1
	, Idle		// �ҋ@
	, FadeOut	// ��ʂ��Â�
	, FadeIn	// ��ʂ𖾂邭
	, Max
};

/*-------------------------------------
/* �t�F�[�h��ʃN���X
-------------------------------------*/
class Fade : public UI
{
public:
	Fade(class Game* game);
	~Fade(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::Fade; }

	// �t�F�[�h�̏�Ԃ��X�V
	void UpdateFadeState(void);

	// ��ʂ��Ó]
	void FadeOut(float deltaTime);

	// ��ʂ𖾓]
	void FadeIn(float deltaTime);

private:
	// �t�F�[�h�p�̃X�v���C�g
	class SpriteRendererComponent* fade_;	

	// �l�R���|�[�l���g�F�t�F�[�h�����s���邩�H
	class BoolParameterComponent*  parameter_is_fade_execute_;

	// �l�R���|�[�l���g�F�t�F�[�h�������������H
	class BoolParameterComponent*  parameter_is_fade_completed_;

	// �t�F�[�h�̏��
	enum class FadeState		   fade_state_;		

private:
	bool				   is_fade_execute_;
	bool				   is_fade_completed_;

	static constexpr int   MAX_FADE_ALPHA_VALUE_ = 255;
	float				   fade_alpha_;

	static constexpr float MAX_EXECUTE_TIME_ = 1.f;
	float				   execute_time_;
};

#endif //Fade_H_
/*=============================================================================
/*		End of File
=============================================================================*/