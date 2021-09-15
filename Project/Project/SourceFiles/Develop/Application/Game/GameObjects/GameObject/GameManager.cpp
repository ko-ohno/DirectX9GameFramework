/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameManager.cpp] �Q�[���i�s�Ǘ��I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���i�s�Ǘ��I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "GameManager.h"

// �G�̐����t�@�N�g��
#include "../../EnemyFactory.h"
#include "../../EnemyFactoryState.h"

// �`��R���|�[�l���g
#include "../Component/RendererComponent/EffectRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/GridGizmoRendererComponent.h"
#include "../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"

// �l�R���|�[�l���g
#include "../Component/ParameterComponent/IntParameterComponent.h"
#include "../Component/ParameterComponent/FloatParameterComponent.h"

// �����R���|�[�l���g
#include "../Component/AudioComponent.h"

#include "../../../ImGui/ImGuiManager.h"

#include "../../Input/InputCheck.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GameManager::GameManager(Game* game)
	: GameObject(game)
	, enemy_factory_(nullptr)
	, grid_gizmo_(nullptr)
	, player_sandbox_gizmo_(nullptr)
	, effect_space_dust_(nullptr)
	, bgm_(nullptr)
	, progress_param_(nullptr)
	, progress_value_(0)
	, score_param_(nullptr)
	, score_value_(0)
{
	// �`�惌�C���[���w��
	this->renderer_layer_type_ = RendererLayerType::Game;

	//�@������
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GameManager::~GameManager(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool GameManager::Init(void)
{
	// �G�l�~�[�̃t�@�N�g���𐶐�
	enemy_factory_ = NEW EnemyFactory(game_);

	// �M�Y���R���|�[�l���g
	{
		// �O���b�h�̕\��
		grid_gizmo_ = NEW GridGizmoRendererComponent(this);

		// �v���C���[�̃T���h�{�b�N�X��\��
		player_sandbox_gizmo_ = NEW BoxGizmoRendererComponent(this);
		player_sandbox_gizmo_->SetScaleX(11.0f);
		player_sandbox_gizmo_->SetScaleY(7.0f);
	}

	// �F���̃`���̃G�t�F�N�g��\��
	effect_space_dust_ = NEW EffectRendererComponent(this);
	effect_space_dust_->SetEffect(EffectType::SpaceDustYellow);
	effect_space_dust_->Play();	//�Đ��J�n 

	// BGM��ݒ�
	bgm_ = NEW AudioComponent(this);
	bgm_->SetSound(SoundType::WonderLand);
	bgm_->SetAudioVolume(0.1f);
	//bgm_->PlayLoop();

	// �l�̍쐬
	{
		progress_param_ = NEW IntParameterComponent(this);
		progress_param_->SetParameterType(ParameterType::Progress);

		score_param_ = NEW IntParameterComponent(this);
		score_param_->SetParameterType(ParameterType::Score);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void GameManager::Uninit(void)
{
	SAFE_DELETE_(enemy_factory_);
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void GameManager::InputGameObject(void)
{
	// �G�l�~�[�̃t�@�N�g���̓��͏���
	if (enemy_factory_ != nullptr)
	{
		enemy_factory_->Input();
	}
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void GameManager::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G�l�~�[�̃t�@�N�g���̍X�V����
	if (enemy_factory_ != nullptr)
	{
		enemy_factory_->Update(deltaTime);
	}

	ImGui::Begin("HUD");
	ImGui::SliderInt("##score_value_", &score_value_, 0, 999);
	ImGui::End();

	// �l�̍X�V
	{
		// �Q�[���̐i�s�x�̒l�̍X�V
		progress_param_->SetInt(progress_value_);

		// �X�R�A�̒l�̍X�V
		score_param_->SetInt(score_value_);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/