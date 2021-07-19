/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ChargeBullet.cpp] �`���[�W�e�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�`���[�W�e�̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "ChargeBullet.h"
#include "../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../Component/ColliderComponent/SphereColliderComponent.h"

#include "../../../Input/InputCheck.h"

#include "../../../../ImGui/ImGuiManager.h"



/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBullet::ChargeBullet(Game* game)
	: SandBox(game)
	, sphere_collider_(nullptr)
	, sphere_collider_gizmo_(nullptr)
	, charge_bullet_state_(ChargeBulletState::None)
	, charge_bullet_state_old_(ChargeBulletState::None)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ChargeBullet::~ChargeBullet(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool ChargeBullet::Init(void)
{
	// �z��̏�����
	{
		// �G�t�F�N�g�ԍ��̓o�^
		effect_type_[0] = EffectType::ChargeBulletState1Charge;
		effect_type_[1] = EffectType::ChargeBulletState2Hold;
		effect_type_[2] = EffectType::ChargeBulletState3Fire;
		effect_type_[3] = EffectType::ChargeBulletState4Bullet;
		effect_type_[4] = EffectType::ChargeBulletState5Explosion;

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = nullptr;
		}
	}

	// �e�ۂ̐���
	{

		for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
		{
			effect_[i] = NEW EffectRendererComponent(this);
			effect_[i]->SetEffect(effect_type_[i]);
			effect_[i]->SetScale(0.5f);
			effect_[i]->SetTranslationX(-4.f + (i*2));
		}
	}

	// �Փ˔���̍쐬
	{
		const float scale = 1.f;

		// ���̏Փ˔���
		sphere_collider_ = NEW SphereColliderComponent(this);
		sphere_collider_->SetRadius(scale);

		// �M�Y���̕`��R���|�[�l���g
		sphere_collider_gizmo_ = NEW SphereGizmoRendererComponent(this);
		sphere_collider_gizmo_->SetScale(scale);
	}

	//effect_[0]->Play();
	effect_[1]->Play();
	//effect_[2]->Play();
	effect_[3]->Play();
	//effect_[4]->Play();

	{
		charge_bullet_state_ = ChargeBulletState::Charge;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void ChargeBullet::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void ChargeBullet::InputGameObject(void)
{
	//if ()
	//{
	//	charge_bullet_state_ = ChargeBulletState::Charge;
	//}
	//else
	//{
	//	charge_bullet_state_ = ChargeBulletState::Hold;
	//}
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateGameObject(float deltaTime)
{
	static float time = 0.f;
	static float time_X = 0.f;


	ImGui::Begin("KeyRepeat");
	ImGui::Text("A:%s", InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_A, 3.f) ? "true" : "false");

	ImGui::Text("X:%s", InputCheck::XInputRepeat(PadIndex::Pad1, XInputButton::XIB_Y, 8.f) ? "true" : "false");


	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_A))
	{
		time += deltaTime;
	}

	if (InputCheck::XInputPress(PadIndex::Pad1, XInputButton::XIB_Y))
	{
		time_X += deltaTime;
	}

	ImGui::Text("%f", time);
	ImGui::Text("%f", time_X);

	ImGui::End();
	// �`���[�W�e�̍X�V
	this->UpdateChargeBullet(deltaTime);

	// �X�e�[�g���؂�ւ�����������Đ������悤��
	if (charge_bullet_state_ != charge_bullet_state_old_)
	{
		this->UpdateChargeBulletState(charge_bullet_state_);
	}

	// 1�t���[���O�̏����X�V
	charge_bullet_state_old_ = charge_bullet_state_;
}

/*-----------------------------------------------------------------------------
/* �`���[�W�e�̏�Ԃ̍X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateChargeBullet(float deltaTime)
{
	static float t = 0;

	t += deltaTime;

	if (t >= 3.f)
	{


		effect_[0]->Play();
		//effect_[1]->Play();
		effect_[2]->Play();
		//effect_[3]->Play();
		effect_[4]->Play();

		t = 0;
	}

	switch (charge_bullet_state_)
	{
	case ChargeBulletState::Charge:
		break;

	case ChargeBulletState::Hold:
		break;

	case ChargeBulletState::Fire:
		break;
	
	case ChargeBulletState::Bullet:
		break;
	
	case ChargeBulletState::Explosion:
		break;
	
	default:
		assert(!"ChargeBullet::UpdateChargeBullet():�`���[�W�e�̃Q�[���I�u�W�F�N�g���s���ȏ������N�����Ă��܂��I");
		break;
	}



	// �`���[�W�e�̈ʒu���X�V
	for (int i = 0; i < MAX_CHARGE_BULLET_STATE; i++)
	{
		effect_[i]->SetTranslation(0.f, 0.f, 0.f);
	}
}

/*-----------------------------------------------------------------------------
/* �`���[�W�e�̏�Ԃ̍X�V����
-----------------------------------------------------------------------------*/
void ChargeBullet::UpdateChargeBulletState(ChargeBulletState chargeBulletState)
{
	switch (chargeBulletState)
	{
	case ChargeBulletState::Charge:
		effect_[static_cast<int>(ChargeBulletState::Charge)]->Play();
		break;

	case ChargeBulletState::Hold:
		effect_[static_cast<int>(ChargeBulletState::Hold)]->Play();
		break;

	case ChargeBulletState::Fire:
		effect_[static_cast<int>(ChargeBulletState::Hold)]->Stop();		// �����Đ�����G�t�F�N�g�̒�~����
		effect_[static_cast<int>(ChargeBulletState::Fire)]->Play();
		break;

	case ChargeBulletState::Bullet:
		effect_[static_cast<int>(ChargeBulletState::Bullet)]->Play();
		break;

	case ChargeBulletState::Explosion:
		effect_[static_cast<int>(ChargeBulletState::Bullet)]->Stop();	// �����Đ�����G�t�F�N�g�̒�~����
		effect_[static_cast<int>(ChargeBulletState::Explosion)]->Play();
		break;

	default:
		assert(!"ChargeBullet::UpdateGameObject():�`���[�W�e�̃Q�[���I�u�W�F�N�g���s���ȏ������N�����Ă��܂��I");
		break;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/