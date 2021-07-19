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
/* �t�F�[�h�Q�[���I�u�W�F�N�g
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

private:
	class SpriteRendererComponent* fade_;
};

#endif //Fade_H_
/*=============================================================================
/*		End of File
=============================================================================*/