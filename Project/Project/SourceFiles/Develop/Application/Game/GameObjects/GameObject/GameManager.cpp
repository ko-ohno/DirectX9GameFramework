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
#include "../../ResourceManager/SaveDataManager.h"

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

// �{�X��HUD
#include "../GameObject/UI/HUD.h"
#include "../GameObject/UI/BossHUD.h"

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

#include "../GameObject/UI/GameOver.h"
#include "../GameObject/UI/GameClear.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GameManager::GameManager(Game* game)
	: GameObject(game)
	, is_secen_change_(false)
	, is_create_player_hud_(false)
	, is_create_boss_hud_(false)
	, enemy_factory_(nullptr)
	, player_(nullptr)
	, boss_(nullptr)
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
	, boss_max_hp_param_(nullptr)
	, boss_max_hp_value_(0.f)
	, boss_hp_param_(nullptr)
	, boss_hp_value_(0.f)
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
	// �l��������
	{
		player_hp_value_ = 1.f;
		boss_hp_value_ = 1.f;
	}

	// �G�l�~�[�̃t�@�N�g���𐶐�
	enemy_factory_ = NEW EnemyFactory(game_);

	// �M�Y���R���|�[�l���g
	{
		// �O���b�h�̕\��
		grid_gizmo_ = NEW GridGizmoRendererComponent(this);
		//grid_gizmo_->IsSetDrawable(false);

		// �v���C���[�̃T���h�{�b�N�X��\��
		player_sandbox_gizmo_ = NEW BoxGizmoRendererComponent(this);
		player_sandbox_gizmo_->SetScaleX(5.5f);
		player_sandbox_gizmo_->SetScaleY(3.5f);
		//player_sandbox_gizmo_->IsSetDrawable(false);
	}

	// �G�t�F�N�g�R���|�[�l���g
	{
		// �F���̃`���̃G�t�F�N�g��\��
		effect_space_dust_ = NEW EffectRendererComponent(this);
		effect_space_dust_->SetEffect(EffectType::SpaceDustYellow);
		effect_space_dust_->Play();	//�Đ��J�n 
	}

	// �l�R���|�[�l���g�̐���
	{
		// �v���C���[
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
	
		// �{�X
		{
			// �{�X�̍ő�HP
			boss_max_hp_param_ = NEW FloatParameterComponent(this);
			boss_max_hp_param_->SetParameterType(ParameterType::BossMaxHP);

			// �{�X��HP
			boss_hp_param_ = NEW FloatParameterComponent(this);
			boss_hp_param_->SetParameterType(ParameterType::BossHP);
		}
	}

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
	// bgm�̒�~
	bgm_->Stop();

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
	// BGM�̐���
	if (bgm_ == nullptr)
	{
		// ���ʂ�ݒ�
		bgm_volume_ = MAX_BGM_VOLUME_;

		bgm_ = NEW AudioComponent(this);
		bgm_->SetSound(SoundType::WonderLand);
		bgm_->SetAudioVolume(bgm_volume_);
		bgm_->PlayLoop();
	}

	// �Q�[���̏�Ԃ��擾
	auto game_state = game_->GetGameState();

	// ��ʐ؂�ւ����s�����H	 
	if (is_secen_change_ == false)
	{
		// �Z�[�u�f�[�^�̃}�l�[�W���ւ̃|�C���^
		auto save_data_manager = game_->GetSaveDataManager();

		const bool is_game_state_game_clear_ = (game_state == Game::GameState::GameClear);
		if (is_game_state_game_clear_)
		{
			NEW GameClear(game_);
			is_secen_change_ = true;

			// ���݂̃X�R�A���Z�[�u�f�[�^�֒ǉ�
			save_data_manager->AddNewSaveData(NEW SaveData(score_value_));
		}

		const bool is_game_state_game_over_ = (game_state == Game::GameState::GameOver);
		if (is_game_state_game_over_)
		{
			NEW GameOver(game_);
			is_secen_change_ = true;

			// ���݂̃X�R�A���Z�[�u�f�[�^�֒ǉ�
			save_data_manager->AddNewSaveData(NEW SaveData(score_value_));
		}
	}

	if (game_state != Game::GameState::Gameplay) { return; }

	// �l�R���|�[�l���g�̍X�V
	this->UpdateParameterComponent(deltaTime);

	// �v���C���[��HUD�𐶐�����
	{
		bool is_game_state_game_play_ = (game_state == Game::GameState::Gameplay);
		if (is_game_state_game_play_)
		{
			if (is_create_player_hud_ == false)
			{
				NEW HUD(game_);
				is_create_player_hud_ = true;
			}
		}
	}

	// �{�X��HUD�𐶐�����
	if (is_create_boss_hud_)
	{
		NEW BossHUD(game_);
		is_create_boss_hud_ = false;
	}

	// BGM�̐؂�ւ�����
	if (is_bgm_change_ == true)
	{
		this->UpdateBGM(deltaTime);
	}

	// �G�̃E�F�[�u�̐���
	{
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
					// �{�X�̐���
					enemy_factory_->ChangeFactoryState(NEW EnemyFactoryState_Last(game_));

					// BGM�̐؂�ւ���L����
					is_bgm_change_ = true;

					// �{�X��HUD�𐶐���L���ɂ���
					is_create_boss_hud_ = true;

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
}

/*-----------------------------------------------------------------------------
/* �l�R���|�[�l���g�̍X�V����
-----------------------------------------------------------------------------*/
void GameManager::UpdateParameterComponent(float deltaTime)
{
	// �v���C���[�ւ̃|�C���^�̎擾
	{
		// �v���C���[�ւ̃|�C���^�́A���擾���H
		if (player_ == nullptr)
		{
			player_ = this->FindGameObject(GameObject::TypeID::Player);
			player_hp_param_->SetFloat(player_hp_value_);
		}

		if (player_ != nullptr)
		{
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
		}
	}

	// �{�X�ւ̃|�C���^�̎擾
	{
		// �{�X�ւ̃|�C���^�́A���擾���H
		if (boss_ == nullptr)
		{
			boss_ = this->FindGameObject(GameObject::TypeID::Boss);
			boss_hp_param_->SetFloat(boss_hp_value_);
		}

		if (boss_ != nullptr)
		{
			//�@�{�X�̒l�R���|�[�l���g������
			auto parameter_components = boss_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// �l�R���|�[�l���g�̌^�𒲂ׂ�
				auto parameter_component_type = parameter_component->GetParameterType();

				// �{�X�ւ̍ő�HP�l�̍X�V
				if (parameter_component_type == ParameterType::BossMaxHP)
				{
					boss_max_hp_value_ = parameter_component->GetFloat();
					boss_max_hp_param_->SetFloat(boss_max_hp_value_);
				}

				// �{�X��HP�l�̍X�V
				if (parameter_component_type == ParameterType::BossHP)
				{
					boss_hp_value_ = parameter_component->GetFloat();
					boss_hp_param_->SetFloat(boss_hp_value_);
				}
			}
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