/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameEffect.cpp] �Q�[���G�t�F�N�g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���G�t�F�N�g�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "GameEffect.h"
#include "../ResourceManager/EffectManager.h"

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
GameEffect::GameEffect(EffectManager* manager, EffectType effectType)
	: effect_manager_(manager)
	, effect_type_id_(EffectType::None)
	, is_loading_complete_(false)
	, effect_(nullptr)
{
	//�G�t�F�N�gID�̐ݒ�
	effect_type_id_ = effectType;

	//�G�t�F�N�g�̓ǂݍ���
	is_loading_complete_ = this->LoadEffect(effectType);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
GameEffect::~GameEffect(void)
{
	SAFE_RELEASE_(effect_);
}

/*-----------------------------------------------------------------------------
/* �ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
bool GameEffect::LoadEffect(const EffectType effectType)
{
	// �G�t�F�N�V�A�̃}�l�[�W���̎擾
	auto effekseer_manager_ = effect_manager_->GetEffekseerManager();

	//���[�g�p�X�ƃt�@�C���p�X�̍���
	auto effect_filepath = effect_manager_->GetEffectRootpath() + effect_manager_->GetEffectFilepathList().at(effectType);

	//string��wstring�֕ϊ�
	std::wstring filepath = this->StringToWString(effect_filepath);

	// �G�t�F�N�g�̍쐬
	effect_ = Effekseer::Effect::Create(effekseer_manager_, (const EFK_CHAR*)filepath.c_str());
	if (effect_ == nullptr)
	{
		//�t�@�C���p�X�ƍŌ�̃f�B���N�g���p�X���擾
		auto filename		= effect_manager_->GetEffectFilepathList().at(effectType);
		auto str_offset_pos = filename.find("/");

		//�t�@�C�������������o��
		filename.erase(0, str_offset_pos +1); // "/" ���I�t�Z�b�g

		//�G���[���b�Z�[�W�̍쐬
		std::string err_msg = "Effect::LoadEffect()�FEffekseer�ɂ��G�t�F�N�g�̍쐬�Ɏ��s���܂����B\nEffectType�F" + filename;
		MessageBox(nullptr
			, err_msg.c_str()
			, "�x��"
			, (MB_OK | MB_ICONWARNING));
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* string��wstring�֕ϊ�
-----------------------------------------------------------------------------*/
std::wstring GameEffect::StringToWString(const std::string& str)
{
	// SJIS �� wstring
	int buf_size = MultiByteToWideChar(CP_ACP
									  , NULL
									  , str.c_str()
									  , -1
									  , (wchar_t*)NULL
									  , NULL);

	// �o�b�t�@�̎擾
	wchar_t* wchar_buf = NEW wchar_t[buf_size];

	// SJIS �� wstring
	MultiByteToWideChar(CP_ACP
					   , 0
					   , str.c_str()
					   , -1
					   , wchar_buf
					   , buf_size);

	// wstring�̐���
	std::wstring wstr(wchar_buf, wchar_buf + buf_size - 1);

	// �o�b�t�@�̔j��
	delete[] wchar_buf;

	// �ϊ����ʂ�Ԃ�
	return wstr;
}


/*=============================================================================
/*		End of File
=============================================================================*/