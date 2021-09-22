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

// �G�l�~�[�̃t�@�N�g���̏�ԃN���X
#include "../../EnemyFactoryState/EnemyFactoryState_1.h"
#include "../../EnemyFactoryState/EnemyFactoryState_2.h"
#include "../../EnemyFactoryState/EnemyFactoryState_3.h"
#include "../../EnemyFactoryState/EnemyFactoryState_4.h"
#include "../../EnemyFactoryState/EnemyFactoryState_5.h"
#include "../../EnemyFactoryState/EnemyFactoryState_6.h"
#include "../../EnemyFactoryState/EnemyFactoryState_Last.h"

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
	, player_(nullptr)
	, grid_gizmo_(nullptr)
	, player_sandbox_gizmo_(nullptr)
	, effect_space_dust_(nullptr)
	, bgm_(nullptr)
	, bgm_volume_(0.f)
	, is_bgm_change_(false)
	, player_max_hp_param_(nullptr)
	, player_max_hp_value_(0.f)
	, player_hp_param_(nullptr)
	, player_hp_value_(0.f)
	, progress_param_(nullptr)
	, progress_value_(0)
	, score_param_(nullptr)
	, score_value_(0)
	, is_enemy_spawn_(false)
	, spawn_count_(0)
	, game_left_time_(0.f)
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
	bgm_volume_ = MAX_BGM_VOLUME_;

	bgm_ = NEW AudioComponent(this);
	bgm_->SetSound(SoundType::WonderLand);
	bgm_->SetAudioVolume(bgm_volume_);
	bgm_->PlayLoop();

	// �l�R���|�[�l���g�̐���
	{
		// �v���C���[�̍ő�HP
		player_max_hp_param_ = NEW FloatParameterComponent(this);
		player_max_hp_param_->SetParameterType(ParameterType::MaxHP);

		// �v���C���[��HP
		player_hp_param_ = NEW FloatParameterComponent(this);
		player_hp_param_->SetParameterType(ParameterType::HP);

		// �Q�[���̐i�s�x
		progress_param_ = NEW IntParameterComponent(this);
		progress_param_->SetParameterType(ParameterType::GameProgress);
		// �Q�[���̃X�R�A
		score_param_ = NEW IntParameterComponent(this);
		score_param_->SetParameterType(ParameterType::Score);
	}

	//enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_Last(game_));


	// �Q�[���̎c�莞��
	game_left_time_ = MAX_SPAWN_TIME_;

	// �{�X�����̐�������
	{
		//game_left_time_ = 0.f;
		//spawn_count_ = 6;
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
	// �l�R���|�[�l���g�̍X�V
	this->UpdateParameterComponent(deltaTime);

	// BGM�̐؂�ւ�����
	if (is_bgm_change_ == true)
	{
		this->UpdateBGM(deltaTime);
	}

	const int MAX_SPAWN_COUNT = 7;
	if (spawn_count_ >= MAX_SPAWN_COUNT) { return; }

	// �G�l�~�[�̃t�@�N�g���̍X�V����
	if (enemy_factory_ != nullptr)
	{
		// ��������t���O��������
		is_enemy_spawn_ = false;

		// �G�l�~�[�𐶐����鍷���̎��Ԃ����߂�
		const float spawn_time = MAX_SPAWN_TIME_ - (SPAWN_DIFF_TIME_ * spawn_count_);

		// �G�l�~�[�̐������s�����H
		const bool is_execute_spawn = ((game_left_time_ <= spawn_time) && (is_enemy_spawn_ == false));
		if (is_execute_spawn)
		{
			if (game_left_time_ >= 0.1f)
			{
				switch (spawn_count_)
				{
				case 0:
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_1(game_));
					break;

				case 1:
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_2(game_));
					break;

				case 2:
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_3(game_));
					break;

				case 3:
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_4(game_));

					// ���݂̃G�t�F�N�g�̒�~
					effect_space_dust_->Stop();

					// �G�t�F�N�g�̐؂�ւ�
					effect_space_dust_->SetEffect(EffectType::SpaceDustBlue);
					effect_space_dust_->Play();
					break;

				case 4:
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_5(game_));
					break;

				case 5:
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_6(game_));
					break;

				default:
					break;
				}
			}
			else
			{
				enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_Last(game_));

				// BGM�̐؂�ւ���L����
				is_bgm_change_ = true;

				// ���݂̃G�t�F�N�g�̒�~
				effect_space_dust_->Stop();

				// �G�t�F�N�g�̐؂�ւ�
				effect_space_dust_->SetEffect(EffectType::SpaceDustRed);
				effect_space_dust_->Play();
			}

			// �����J�E���g�����Z
			spawn_count_++;

			// �����������Ƃ��L��
			is_enemy_spawn_ = true;
		}

		enemy_factory_->Update(deltaTime);
	}
}

/*-----------------------------------------------------------------------------
/* �l�R���|�[�l���g�̍X�V����
-----------------------------------------------------------------------------*/
void GameManager::UpdateParameterComponent(float deltaTime)
{
	// �ő�HP�ւ̃|�C���^�́A�擾�ς݂��H
	if (player_ == nullptr)
	{
		player_ = this->FindGameObject(GameObject::TypeID::Player);
	}

	// null�`�F�b�N
	if (player_ == nullptr)
	{
		assert(!"GameManager::UpdateParameterComponent:�v���C���[�ւ̃|�C���^���hnullptr�h�ł���");
		return;
	}

	//�@�v���C���[�̒l�R���|�[�l���g������
	auto parameter_components = player_->GetParameterComponents();
	for (auto parameter_component : parameter_components)
	{
		// �l�R���|�[�l���g�̌^�𒲂ׂ�
		auto parameter_component_type = parameter_component->GetParameterType();

		// �v���C���[�̍ő�HP�l�̍X�V
		if (parameter_component_type == ParameterType::MaxHP)
		{
			player_max_hp_value_ = parameter_component->GetFloat();
			player_max_hp_param_->SetFloat(player_max_hp_value_);
		}

		// �v���C���[��HP�l�̍X�V
		if (parameter_component_type == ParameterType::HP)
		{
			player_hp_value_ = parameter_component->GetFloat();
			player_hp_param_->SetFloat(player_hp_value_);
		}
	}

	// �Q�[���̐i�s�x�̒l�̍X�V
	{
		game_left_time_ -= deltaTime;

		if (game_left_time_ <= 0.f)
		{
			game_left_time_ = 0.f;
		}
		
		progress_value_ = static_cast<int>(game_left_time_);
		progress_param_->SetInt(progress_value_);
	}


	//ImGui::Begin("HUD");
	//ImGui::SliderInt("##score_value_", &score_value_, 0, 999);
	//ImGui::End();

	// �X�R�A�̒l�̍X�V
	{
		score_value_ = score_param_->GetInt();
		score_param_->SetInt(score_value_);
	}
}

/*-----------------------------------------------------------------------------
/* BGM�̍X�V����
-----------------------------------------------------------------------------*/
void GameManager::UpdateBGM(float deltaTime)
{
	// ���ʂ�������
	bgm_volume_ -= deltaTime;
	bgm_->SetAudioVolume(bgm_volume_);

	// BGM�̐؂�ւ�
	if (bgm_volume_ <= 0.f)
	{
		// ���݂�BGM���~
		bgm_->Stop();

		// BGM�̐؂�ւ��ƍĐ�
		bgm_->SetSound(SoundType::JetPenguin_2nd);
		bgm_->SetAudioVolume(MAX_BGM_VOLUME_);
		bgm_->PlayLoop();

		is_bgm_change_ = false;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/