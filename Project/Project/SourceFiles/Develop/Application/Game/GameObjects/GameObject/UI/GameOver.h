/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameOver.h] �Q�[���I�[�o�[��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���I�[�o�[��ʃN���X
=============================================================================*/
#ifndef GAME_OVER_H_
#define	GAME_OVER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../UI.h"

/*-------------------------------------
/* �Q�[���I�[�o�[��ʃN���X
-------------------------------------*/
class GameOver : public UI
{
public:
	GameOver(class Game* game);
	~GameOver(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameOver; }

private:
};

#endif //GAME_OVER_H_
/*=============================================================================
/*		End of File
=============================================================================*/