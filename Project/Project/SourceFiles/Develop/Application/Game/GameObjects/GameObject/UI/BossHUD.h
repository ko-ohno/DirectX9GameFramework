/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BossHUD.h] �{�X��HUD�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�X��HUD�N���X
=============================================================================*/
#ifndef BOSS_HUD_H_
#define	BOSS_HUD_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/*�@�{�X��HUD�N���X
-------------------------------------*/
class BossHUD : public UI
{
public:
	BossHUD(class Game* game);
	~BossHUD(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;


private:
	// �l�R���|�[�l���g�擾�p�Q�[���}�l�[�W���[�ւ̃|�C���^
	class GameObject*				game_manager_;

private:
	// �{�X�̗̑̓Q�[�W
	class SpriteRendererComponent*	health_bar_;
	class SpriteRendererComponent*	health_bar_blank_;
	class SpriteRendererComponent*	health_bar_bg_;

	// �ő�̗̑͒l
	float	max_hp_value_;

	// �̗͒l
	float	hp_value_;

	// ���݂�HP�̊���
	float	hp_rate_;

private:



};


#endif //BOSS_HUD_H_
/*=============================================================================
/*		End of File
=============================================================================*/