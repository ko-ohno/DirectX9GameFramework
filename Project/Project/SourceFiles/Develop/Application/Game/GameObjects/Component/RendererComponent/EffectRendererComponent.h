/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectRendererComponent.h]  �G�t�F�N�g�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�t�F�N�g�R���|�[�l���g
=============================================================================*/
#ifndef EFFECT_COMPONENT_H_
#define	EFFECT_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../RendererComponent.h"

/*-------------------------------------
/* �G�t�F�N�g�R���|�[�l���g�N���X
-------------------------------------*/
class EffectRendererComponent : public RendererComponent
{
public:
	EffectRendererComponent(class GameObject* owner, int drawOrder = 100);
	~EffectRendererComponent(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	// �G�t�F�N�g�̐ݒ�
	void SetEffect(EffectType effectTypeID);

	// �G�t�F�N�g���̎擾
	class Effect* GetEffect(void);

	virtual TypeID GetComponentType() const override { return TypeID::EffectRendererComponent; };

	//
	// �G�t�F�N�g�̍Đ�
	//

	void Play(void);
	void Play(const D3DXVECTOR3& position);
	void Play(float posX, float posY, float posZ);
	
	//
	// �G�t�F�N�g�̈ꎞ��~
	//

	void Paused(bool isPaused);

	//
	// �G�t�F�N�g�̒�~
	//

	void Stop(void);

	//
	// �G�t�F�N�g��s�p�����̍X�V
	//

	void SetBaseMatirx(const D3DXMATRIX& matrix);

private:
	// �G�t�F�N�g�̊Ǘ���
	class EffectManager* effect_manager_;

	// Effekseer�̃}�l�[�W���ւ̃|�C���^
	Effekseer::Manager*	 effekseer_manager_;

	// �G�t�F�N�g�̃f�[�^
	class Effect*		 effect_;
};

#endif //EFFECT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/