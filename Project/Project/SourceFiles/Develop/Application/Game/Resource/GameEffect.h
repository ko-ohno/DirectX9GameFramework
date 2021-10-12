/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameEffect.h] �Q�[���G�t�F�N�g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���G�t�F�N�g�N���X
=============================================================================*/
#ifndef GAME_EFFECT_H_
#define	GAME_EFFECT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../ResourceManager/EffectManager.h"


/*-------------------------------------
/* �Q�[���G�t�F�N�g�N���X
-------------------------------------*/
class GameEffect
{
public:
	GameEffect(class EffectManager* manager, EffectType effectType);
	~GameEffect(void);

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
};

#endif //GAME_EFFECT_H_
/*=============================================================================
/*		End of File
=============================================================================*/
