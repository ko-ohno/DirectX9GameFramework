/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MeshManager.cpp] ���b�V���Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���b�V���Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "EffectManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"
#include "../Resource/GameEffect.h"

//�G�t�F�N�g�̖��O���X�g
const char* EffectManager::EffectTypeNames[static_cast<int>(EffectType::Max)] = {
	"Sample"
	, "BlueDust"
	, "YellowDust"
	, "RedDust"
	
	, "BlueMuzzluFrash"
	, "YellowMuzzluFrash"
	, "RedMuzzleFlash"

	, "ChargeBulletState1Charge"
	, "ChargeBulletState2Hold"
	, "ChargeBulletState3Fire"
	, "ChargeBulletState4Bullet"
	, "ChargeBulletState5Explosion"

	, "BlueLaser"
	, "AfterBurner"
};

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
EffectManager::EffectManager(Game* game)
	: game_(game)
	, manager_(nullptr)
	, renderer_(nullptr)
	, sound_(nullptr)
	, xaudio2_(nullptr)
	, xaudio2_master_(nullptr)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
EffectManager::~EffectManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
EffectManager* EffectManager::Create(Game* game)
{
	return NEW EffectManager(game);
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool EffectManager::StartUp(void)
{
	//���g�̏�����
	const bool effect_manager_init = this->Init();
	if (effect_manager_init == false)
	{
		assert(!"EffectManager::StartUp()�F�G�t�F�N�g�}�l�[�W���̏������Ɏ��s���܂����B");
		return false;
	}

	//�G�t�F�N�g�̓ǂݍ��ݏ���
	{
		//this->LoadEffect(EffectType::AfterBurner);

		// �`���[�W�e�̃G�t�F�N�g�̓ǂݍ���
		this->LoadEffect(EffectType::ChargeBulletState1Charge);
		this->LoadEffect(EffectType::ChargeBulletState2Hold);
		this->LoadEffect(EffectType::ChargeBulletState3Fire);
		this->LoadEffect(EffectType::ChargeBulletState4Bullet);
		this->LoadEffect(EffectType::ChargeBulletState5Explosion);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void EffectManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool EffectManager::Init(void)
{
	//�G�t�F�N�g�̃��[�g�p�X��ݒ�
	effect_root_path_ = "Assets/ParticleEffects/";

	//�G�t�F�N�g�̂̃��X�g��������
	effect_list_.clear();

	//�G�t�F�N�g�̃t�@�C���p�X�̃��X�g��������
	unmap_effect_path_list_.clear();
	{
		//
		// �G�t�F�N�g�t�@�C���̓ǂݍ��ݗp�t�@�C���p�X���X�g�̍쐬  
		//
		{
			//unmap_effect_path_list_[EffectType::Sample] = "Sample";

			// �F���S�~�̃p�[�e�B�N��
			unmap_effect_path_list_[EffectType::SpaceDustYellow]  = "SpaceDust/yellow_dust.efk";
			unmap_effect_path_list_[EffectType::SpaceDustBlue]	  = "SpaceDust/blue_dust.efk";
			unmap_effect_path_list_[EffectType::SpaceDustRed]	  = "SpaceDust/red_dust.efk";

			// �}�Y���t���b�V���̃G�t�F�N�g
			unmap_effect_path_list_[EffectType::MuzzluFrashGreen]  = "Shot/shot_green.efk";
			unmap_effect_path_list_[EffectType::MuzzluFrashBlue]   = "Shot/shot_blue.efk";
			unmap_effect_path_list_[EffectType::MuzzluFrashOrange] = "Shot/shot_orange.efk";

			// �`���[�W�e�̃G�t�F�N�g
			unmap_effect_path_list_[EffectType::ChargeBulletState1Charge]	 = "ChargeBullet/cb_state_1_charge.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState2Hold]		 = "ChargeBullet/cb_state_2_hold.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState3Fire]		 = "ChargeBullet/cb_state_3_fire.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState4Bullet]	 = "ChargeBullet/cb_state_4_bullet.efk";
			unmap_effect_path_list_[EffectType::ChargeBulletState5Explosion] = "ChargeBullet/cb_state_5_explosion.efk";

			// �Ԃ����[�U�[�̃G�t�F�N�g
			unmap_effect_path_list_[EffectType::RedLaser]	 = "Laser/RedLaser.efk";

			//�A�t�^�[�o�[�i�[�̃G�t�F�N�g
			unmap_effect_path_list_[EffectType::AfterBurner] = "AfterBurner/after_burner.efk";
		}
	}


	
	// COM�R���|�[�l���g�́AApplicationManager::Init()�ŏ������ς�
	{
		//HRESULT hr;
		//hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		//if (FAILED(hr))
		//{
		//	assert(!"EffectManager::Init()�FCOM�R���|�[�l���g�̏������Ɏ��s���܂����I");
		//	return false;
		//}
	}

	//XAudio2�̏��������s��
	{
		HRESULT hr;

		// XAudio�̃C���X�^���X���쐬
		hr = XAudio2Create(&xaudio2_);
		if (FAILED(hr))
		{
			assert(!"EffectManager::Init()�FXAudio�̃C���X�^���X�̍쐬�Ɏ��s���܂����B");
			return false;
		}

		// XAudio�̃}�X�^�[�{�C�X�쐬
		hr = xaudio2_->CreateMasteringVoice(&xaudio2_master_);	
		if (FAILED(hr))
		{
			assert(!"EffectManager::Init()�FXAudio�̃}�X�^�[�{�C�X�̍쐬�Ɏ��s���܂����B");
			return false;
		}
	}

	// �G�t�F�N�g�̍Đ��p�̐ݒ��������
	{	
			
		// �ő�ŏo�͂���X�v���C�g�̐�
		const int maximize_render_sprite_count = 2000;

		// �`��p�C���X�^���X�̐���
		renderer_ = EffekseerRendererDX9::Renderer::Create(*DX9Graphics::GetLPD3DDevice(), maximize_render_sprite_count);
		const bool renderer_initialize_failed = (renderer_ == nullptr);
		if (renderer_initialize_failed)
		{
			assert(!"EffectManager::Init()�F�`��p�C���X�^���X�̐����Ɏ��s���܂����B");
			return false;
		}
	
		// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
		manager_ = Effekseer::Manager::Create(maximize_render_sprite_count);
		const bool manager_initialize_failed = (manager_ == nullptr);
		if (manager_initialize_failed)
		{
			assert(!"EffectManager::Init()�F�G�t�F�N�g�Ǘ��p�C���X�^���X�̐����Ɏ��s���܂����B");
			return false;
		}

		// �`��p�C���X�^���X����`��@�\��ݒ�
		manager_->SetSpriteRenderer(renderer_->CreateSpriteRenderer());
		manager_->SetRibbonRenderer(renderer_->CreateRibbonRenderer());
		manager_->SetRingRenderer(renderer_->CreateRingRenderer());
		manager_->SetTrackRenderer(renderer_->CreateTrackRenderer());
		manager_->SetModelRenderer(renderer_->CreateModelRenderer());


		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		manager_->SetTextureLoader(renderer_->CreateTextureLoader());
		manager_->SetModelLoader(renderer_->CreateModelLoader());

		// �����Đ��p�C���X�^���X�̐���
		sound_ = EffekseerSound::Sound::Create(xaudio2_, 16, 16);
		const bool sound_initialize_failed = (sound_ == nullptr);
		if (sound_initialize_failed)
		{
			assert(!"EffectManager::Init()�F�����Đ��p�C���X�^���X�̐����Ɏ��s���܂����B");
			return false;
		}

		// �����Đ��p�C���X�^���X����Đ��@�\���w��
		manager_->SetSoundPlayer(sound_->CreateSoundPlayer());

		// �����Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		manager_->SetSoundLoader(sound_->CreateSoundLoader());
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void EffectManager::Uninit(void)
{
	//�ǂݍ���ł���G�t�F�N�g�̃f�[�^���ꊇ�j��
	while (!effect_list_.empty())
	{
		delete effect_list_.back();
		effect_list_.back() = nullptr;
		effect_list_.pop_back();
	}


	// �G�t�F�N�g�̍Đ��p�̐ݒ���I����
	{
		// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
		manager_->Destroy();

		// ���Đ��p�C���X�^���X��j��
		sound_->Destroy();

		// �`��p�C���X�^���X��j��
		renderer_->Destroy();

		// XAudio2�̃}�X�^�[�{�C�X�����
		if (xaudio2_master_ != nullptr)
		{
			xaudio2_master_->DestroyVoice();
			xaudio2_master_ = nullptr;
		}

		// XAudio�̉��
		ES_SAFE_RELEASE(xaudio2_);

		// COM�R���|�[�l���g�́AApplicationManager::Uninit()�ŏI�����ς�
		//CoUninitialize();
	}
}

/*-----------------------------------------------------------------------------
/* ���ׂẴG�t�F�N�g���ꎞ��~
-----------------------------------------------------------------------------*/
void EffectManager::SetPausedToAllEffect(bool isPaused)
{
	manager_->SetPausedToAllEffects(isPaused);
}

/*-----------------------------------------------------------------------------
/* DirectX�̍s���Effekseer��43�s��ɕϊ�
-----------------------------------------------------------------------------*/
const Effekseer::Matrix43 EffectManager::Convert43Matrix(const D3DXMATRIX& d3dxMatrix)
{
	// Effekseer�ւ̕ϊ��s��
	Effekseer::Matrix43 convert_matrix_43;

	// DirectX�̍s���Effekseer�̍s��ɕϊ�
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 3; j++)
		{
			convert_matrix_43.Value[i][j] = d3dxMatrix.m[i][j];
		}
	}
	return convert_matrix_43;
}

/*-----------------------------------------------------------------------------
/* DirectX�̍s���Effekseer��44�s��ɕϊ�
-----------------------------------------------------------------------------*/
const Effekseer::Matrix44 EffectManager::Convert44Matrix(const D3DXMATRIX& d3dxMatrix)
{
	// Effekseer�ւ̕ϊ��s��
	Effekseer::Matrix44 convert_matrix_44;

	// DirectX�̍s���Effekseer�̍s��ɕϊ�
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			convert_matrix_44.Values[i][j] = d3dxMatrix.m[i][j];
		}
	}
	return convert_matrix_44;
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
GameEffect* EffectManager::LoadEffect(EffectType effectTypeID)
{
	auto effect = this->FindEffect(effectTypeID);
	if (effect != nullptr)
	{
		return effect;
	}
	else
	{
		//���b�V�����Ȃ�������
		const bool is_mesh_list_out_of_range = ((effectTypeID <= EffectType::None)
											   || (effectTypeID >= EffectType::Max));
		if (is_mesh_list_out_of_range)
		{
			assert("�͈͊O�̃G�t�F�N�gID���Q�Ƃ��悤�Ƃ��Ă��܂��I");
			return nullptr;
		}
		this->AddEffect(NEW GameEffect(this, effectTypeID));
	}
	return this->FindEffect(effectTypeID);
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̉������
-----------------------------------------------------------------------------*/
void EffectManager::ReleaseEffect(EffectType effectTypeID)
{
	for (auto effect : effect_list_)
	{
		auto id = effect->GetEffectTypeID();

		if (id == effectTypeID)
		{
			delete effect;
		}
	}
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̌�������
-----------------------------------------------------------------------------*/
GameEffect* EffectManager::FindEffect(EffectType effectTypeID)
{
	//�G�t�F�N�g���X�g�̌���
	for (auto effect : effect_list_)
	{
		//���݂̒����Ώۂ���ID���擾
		auto id = effect->GetEffectTypeID();

		//�擾����ID��effectTypeID����v���邩
		if (id == effectTypeID)
		{
			return effect;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̒ǉ�����
-----------------------------------------------------------------------------*/
void EffectManager::AddEffect(GameEffect* effect)
{
	effect_list_.emplace_back(effect);
}

/*-----------------------------------------------------------------------------
/* �G�t�F�N�g�̍폜����
-----------------------------------------------------------------------------*/
void EffectManager::RemoveEffect(GameEffect* effect)
{
	auto iter = std::find(effect_list_.begin()	//�͈�0�`
						 , effect_list_.end()	//�͈͍ő�܂�
						 , effect);				//�T���Ώ�

	if (iter != effect_list_.end())
	{
		effect_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/