/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteTest.h] �X�v���C�g�̃e�X�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�̃e�X�g�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef SPRITE_TEST_H_
#define	SPRITE_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../GameObject.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �N���X
-------------------------------------*/
class SpriteTest : public GameObject
{
public:
	SpriteTest(class Game* game);
	~SpriteTest(void);

	static SpriteTest* Create(class Game* game);

	bool Init(void);	//������
	void Uninit(void);	//�I����
	
	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class SpriteRendererComponent* sprite_;
	 
	class SpriteRendererComponent* sprite_a_;

	class SpriteRendererComponent* sprite_b_;
};


#endif //SPRITE_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/