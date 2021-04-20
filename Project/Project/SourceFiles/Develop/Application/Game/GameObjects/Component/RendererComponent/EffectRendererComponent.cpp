/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectRendererComponent.cpp] �G�t�F�N�g�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�t�F�N�g�R���|�[�l���g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "EffectRendererComponent.h"
#include "../../GameObject.h"
#include "../../../../Math.h"
#include "../../../Resource/Effect.h"
#include "../../GameObject/Camera.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EffectRendererComponent::EffectRendererComponent(GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, effect_(nullptr)
	, effekseer_manager_(nullptr)
{
	//�`�惌�C���[���w��
	renderer_layer_type_ = RendererLayerType::ParticleEffect;

	//���g�̏�����
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EffectRendererComponent::~EffectRendererComponent(void)
{
	//���g�̏I����
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EffectRendererComponent::Init(void)
{
	this->shader_type_ = ShaderType::ParticleEffect;
	
	//	�G�t�F�N�g�̃}�l�[�W���̎擾
	effect_manager_ = owner_->GetGame()->GetEffectManager();
	const bool effect_manager_init = (effect_manager_ != nullptr);
	if (effect_manager_init == false)
	{
		assert(!"EffectRendererComponent::Init()�F�G�t�F�N�g�̃}�l�[�W���̎擾�Ɏ��s���܂����B");
		return false;
	}

	//	Effekseer�ւ̃}�l�[�W���̎擾
	effekseer_manager_ = effect_manager_->GetEffekseerManager();
	const bool effekseer_manager_init = (effekseer_manager_ != nullptr);
	if (effekseer_manager_init == false)
	{
		assert(!"EffectRendererComponent::Init()�FEffekseer�ւ̃}�l�[�W���̎擾�Ɏ��s���܂����B");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�t�F�N�g�ւ̃C���X�^���X���Ȃ�������`�悵�Ȃ�
	if (effect_ == nullptr)
	{
		assert(!"EffectRendererComponent::Update()�F�G�t�F�N�g��񂪐ݒ肳��Ă��܂���B");
		return;
	}

	// �p�����̍X�V
	{
		//��]���
		D3DXMATRIX rotation_matrix = this->rotation_matrix_;

		//�ʒu���A�g�k���
		D3DXVECTOR3 position = this->position_;
		D3DXVECTOR3 scale = this->scale_;


		//�g�k�̃x�N�g���l�ɁA��]�s��̒l�����킦�Čv�Z

		//X��
		world_matrix_._11 = scale.x * rotation_matrix._11;
		world_matrix_._12 = scale.x * rotation_matrix._12;
		world_matrix_._13 = scale.x * rotation_matrix._13;

		//Y��
		world_matrix_._21 = scale.y * rotation_matrix._21;
		world_matrix_._22 = scale.y * rotation_matrix._22;
		world_matrix_._23 = scale.y * rotation_matrix._23;

		//Z��
		world_matrix_._31 = scale.z * rotation_matrix._31;
		world_matrix_._32 = scale.z * rotation_matrix._32;
		world_matrix_._33 = scale.z * rotation_matrix._33;

		//���s�ړ�
		world_matrix_._41 = position.x;
		world_matrix_._42 = position.y;
		world_matrix_._43 = position.z;

		//W����
		world_matrix_._14 = world_matrix_._24 = world_matrix_._34 = 0.0f;

		//1.0f�ɐݒ肷�邱�Ƃ�world_matrix_._4*���x�N�g����
		world_matrix_._44 = 1.0f;
	}

	//�G�t�F�N�g�̕\�����W���X�V
	effekseer_manager_->SetBaseMatrix(*effect_->GetEffectHandle(), this->effect_manager_->Convert43Matrix(world_matrix_));

	//�G�t�F�N�g���n���h���P�ʂōX�V
	effekseer_manager_->UpdateHandle(*effect_->GetEffectHandle());
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Draw(Shader* shader, Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
	UNREFERENCED_PARAMETER(camera);
	
	//�G�t�F�N�g���n���h���P�ʂŕ`��
	effekseer_manager_->DrawHandle(*effect_->GetEffectHandle());
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̐ݒ�
-----------------------------------------------------------------------------*/
void EffectRendererComponent::SetEffect(EffectType effectTypeID)
{
	//�G�t�F�N�g�̓ǂݍ���
	this->effect_ = owner_->GetGame()->GetEffectManager()->LoadEffect(effectTypeID);
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g���̎擾
-----------------------------------------------------------------------------*/
Effect* EffectRendererComponent::GetEffect(void)
{
	//���b�V�����̎擾
	if (this->effect_ == nullptr)
	{
		assert(!"EffectRendererComponent::GetEffect():�G�t�F�N�g��񂪐ݒ肳��Ă��܂���I");
	}
	return effect_;
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g���̎擾
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Play(void)
{
	//�G�t�F�N�g�̃n���h����������
	*effect_->GetEffectHandle() = effekseer_manager_->Play(effect_->GetEffect(), Effekseer::Vector3D(0, 0, 0));
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g���̎擾
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Play(const D3DXVECTOR3& position = D3DXVECTOR3(0.f, 0.f, 0.f))
{
	//�G�t�F�N�g�̃n���h����������
	*effect_->GetEffectHandle() = effekseer_manager_->Play(effect_->GetEffect(), Effekseer::Vector3D(position.x, position.y, position.z));
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�Đ�����
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Play(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f)
{
	//�G�t�F�N�g�̃n���h����������
	*effect_->GetEffectHandle() = effekseer_manager_->Play(effect_->GetEffect(), Effekseer::Vector3D(posX, posY, posZ));
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�ꎞ��~����
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Paused(bool isPaused)
{
	//�G�t�F�N�g�̃n���h����������
	effekseer_manager_->SetPaused(*effect_->GetEffectHandle(), isPaused);
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g��~����
-----------------------------------------------------------------------------*/
void EffectRendererComponent::Stop(void)
{
	//�G�t�F�N�g�̃n���h����������
	effekseer_manager_->StopEffect(*effect_->GetEffectHandle());
}

/*=============================================================================
/*		End of File
=============================================================================*/