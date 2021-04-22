/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[XFileMesh.h] X�t�@�C�����b�V���N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FX�t�@�C�����b�V���N���X
=============================================================================*/
#ifndef EFFECT_H_
#define	EFFECT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../Manager/EffectManager.h"


/*-------------------------------------
/* �G�t�F�N�g�N���X
-------------------------------------*/
class Effect
{
public:
	Effect(class EffectManager* manager, EffectType effectType);
	~Effect(void);

	// �G�t�F�N�g�̓ǂݍ���
	bool LoadEffect(const EffectType effectType);

	// �e�N�X�`���̓ǂݍ��݂��ł��Ă��邩
	bool IsGetLoadCompleted(void) { return is_loading_complete_; }

	//
	// �G�t�F�N�g�̃f�[�^�擾�֐�
	//

	// �G�t�F�N�gID�̎擾
	EffectType GetEffectTypeID(void) { return effect_type_id_; }

	// �G�t�F�N�g���̎擾
	Effekseer::Effect* GetEffect(void) { return effect_; }

	// �G�t�F�N�g�̃n���h���擾
	Effekseer::Handle* GetEffectHandle(void) { return &handle_; }

private:
	std::wstring StringToWString(const std::string& str);

private:
	static constexpr int ERROR_CODE_EFFECT_HANDLE = -1;

	// �G�t�F�N�g�̏��L��
	class EffectManager* effect_manager_;

	//
	// �G�t�F�N�g�̂̃f�[�^
	//

	bool				is_loading_complete_;	// ���[�h���������Ă��邩

	EffectType			effect_type_id_;		// �G�t�F�N�g��ID

	Effekseer::Effect*	effect_;				// ���삷��G�t�F�N�g
	
	Effekseer::Handle	handle_;				// �G�t�F�N�g����p�̃n���h��
};

#endif //EFFECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/
