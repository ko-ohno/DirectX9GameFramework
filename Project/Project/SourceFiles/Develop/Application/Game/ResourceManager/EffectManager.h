/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectManager.h] ���b�V���Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�G�t�F�N�g�̊Ǘ��N���X
=============================================================================*/
#ifndef EFFECT_MANAGER_H_
#define	EFFECT_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../External/Effekseer/include/Effekseer.h"
#include "../../../../External/Effekseer/include/EffekseerRendererDX9.h"
#include "../../../../External/Effekseer/include/EffekseerSoundXAudio2.h"

// ���Đ��p���C�u�����̌Ăяo��
#include <X3DAudio.h>

// ���Đ�
#pragma comment(lib, "X3DAudio.lib")

//���C�u�����̃����N
#if defined(_DEBUG)||(DEBUG)
#pragma comment(lib, "Effekseer/Debug/Effekseer.Debug.lib")
#pragma comment(lib, "Effekseer/Debug/EffekseerRendererDX9.Debug.lib")
#pragma comment(lib, "Effekseer/Debug/EffekseerSoundXAudio2.Debug.lib")
#else			
#pragma comment(lib, "Effekseer/Release/Effekseer.Release.lib")
#pragma comment(lib, "Effekseer/Release/EffekseerRendererDX9.Release.lib")
#pragma comment(lib, "Effekseer/Release/EffekseerSoundXAudio2.Release.lib")
#endif


/*-------------------------------------
/* �G�t�F�N�g�̎��
-------------------------------------*/
enum class EffectType
{
	None = -1
	, Sample
	, SpaceDustBlue
	, SpaceDustYellow
	, SpaceDustRed

	, MuzzluFrashBlue
	, MuzzluFrashGreen
	, MuzzluFrashOrange

	, ChargeBulletState1Charge
	, ChargeBulletState2Hold
	, ChargeBulletState3Fire
	, ChargeBulletState4Bullet
	, ChargeBulletState5Explosion

	, AfterBurner
	, Max
};

/*-------------------------------------
/* �G�t�F�N�g�̊Ǘ��N���X
-------------------------------------*/
class EffectManager
{
public:
	static const char* EffectTypeNames[static_cast<int>(EffectType::Max)];

public:
	EffectManager(class Game* game);
	~EffectManager(void);

	static EffectManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);
	void Uninit(void);

public:
	// ���ׂẴG�t�F�N�g���ꎞ��~
	void SetPausedToAllEffect(bool isPaused);

	// �G�t�F�N�g�p��43�s��֕ϊ�
	const Effekseer::Matrix43 Convert43Matrix(const D3DXMATRIX& d3dxMatrix);

	// �G�t�F�N�g�p��44�s��֕ϊ�
	const Effekseer::Matrix44 Convert44Matrix(const D3DXMATRIX& d3dxMatrix);

	//�e�N�X�`���̃��[�g�p�X�̎擾
	std::string GetEffectRootpath(void) const { return effect_root_path_; }

	//���b�V���̓ǂݍ���
	class GameEffect* LoadEffect(EffectType effectTypeID);

	//���b�V���̉��
	void ReleaseEffect(EffectType effectTypeID);

	//���b�V������������
	class GameEffect* FindEffect(EffectType effectTypeID);

	//
	// �G�t�F�N�g�̒ǉ��ƍ폜
	//

	void AddEffect(class GameEffect* effect);
	void RemoveEffect(class GameEffect* effect);

	std::unordered_map<enum class EffectType, std::string> GetEffectFilepathList(void) { return unmap_effect_path_list_; }

	class Game* GetGame(void) { return game_; }
	class Effekseer::Manager* GetEffekseerManager(void) { return manager_; }
	class EffekseerRendererDX9::Renderer* GetEffekseerRenderer(void) { return renderer_; }

private:
	Effekseer::Manager*					manager_;			//Effekseer���̃��C�u�����̃}�l�[�W��
	EffekseerRendererDX9::Renderer*		renderer_;			//Effekseer���̃����_���[
	EffekseerSound::Sound*				sound_;				//Effekseer���̃T���E�h�Ǘ��N���X

	IXAudio2*							xaudio2_;			//XAudio�ւ̃|�C���^
	IXAudio2MasteringVoice*				xaudio2_master_;	//XAudio�ւ̃}�X�^�[�{�C�X

private:
	//�}�l�[�W���[�̏��L��
	class Game* game_;

	//�G�t�F�N�g�̃��[�g�p�X
	std::string effect_root_path_;

	//�G�t�F�N�g�̃p�X���X�g
	std::unordered_map<enum class EffectType, std::string> unmap_effect_path_list_;

	//���b�V�����X�g�̃R���e�i
	std::vector<class GameEffect*> effect_list_;
};

#endif //EFFECT_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/