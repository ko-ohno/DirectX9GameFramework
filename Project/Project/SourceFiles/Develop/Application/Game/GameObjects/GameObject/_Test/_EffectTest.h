/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectTest.h] �G�t�F�N�g�e�X�g�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�t�F�N�g�e�X�g�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef EFFECT_TEST_H_
#define	EFFECT_TEST_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../GameObject.h"


/*-------------------------------------
/* �G�t�F�N�g�e�X�g�Q�[���I�u�W�F�N�g
-------------------------------------*/
class EffectTest : public GameObject
{
public:
	EffectTest(class Game* game);
	~EffectTest(void);

	static EffectTest* Create(class Game* game);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

private:
	class EffectRendererComponent* effect_renderer_comp_;

	class EffectRendererComponent* effect_renderer_comp_a;
	class EffectRendererComponent* effect_renderer_comp_b;

};

#endif //EFFECT_TEST_H_
/*=============================================================================
/*		End of File
=============================================================================*/