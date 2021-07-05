/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[HUD.h] �Q�[����ʂ�HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ʂ�HUD�̋������`�����N���X
=============================================================================*/
#ifndef HUD_H_
#define	HUD_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �Q�[����ʂ�HUD�N���X
-------------------------------------*/
class HUD : public UI
{
public:
	HUD(class Game* game);
	~HUD(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::HUD; }

	// �̗�
	void UpdateHealthBarHUD(float deltaTime);
	
	//�@�S�[���܂ł̋���
	void UpdateGoalMeterHUD(float deltaTime);

	//�@�S�[���܂ł̋���
	void UpdateScoreHUD(float deltaTime);

private:
	// �̗̓Q�[�W
	class SpriteRendererComponent* health_bar_;
	class SpriteRendererComponent* health_bar_blank_;
	class SpriteRendererComponent* health_bar_bg_;

	// �̗͒l
	float health_value_;

private:
	// �S�[���܂ł̋�����HUD
	class SpriteRendererComponent* meter_center_bg_;
	class SpriteRendererComponent* meter_left_bg_;
	class SpriteRendererComponent* meter_right_bg_;

	// �������̕\��
	class SpriteDigitRendererComponent* distance_digit_;

	// �S�[���܂ł̋����̒l
	int distance_value_;


private:
	// �������̕\��
	class SpriteDigitRendererComponent* score_digit_;

	// �S�[���܂ł̋����̒l
	int score_value_;
};

#endif //HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/