/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SoundManager.h] �T�E���h�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�T�E���h�Ǘ��N���X
=============================================================================*/
#ifndef SOUND_MANAGER_H_
#define	SOUND_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include <XAudio2.h>


/*-------------------------------------
/* �T�E���h�̎��
-------------------------------------*/
enum class SoundType
{
	None = -1
	, Sample

	// BGM
	, WonderLand
	, JetPenguin
	, JetPenguin_2nd
	, Kemono

	// SE
	, SelectSound			// �I��
	, DamageBoss			// �{�X�Ƀ_���[�W
	, DamagePlayer			// �v���C���[�Ƀ_���[�W
	, DangerAlert			// �댯�ʒm
	, LockonAlert			// ���b�N�I���ʒm
	, BodyPressAttack		// �̓�����U���̉�
	, BodyPressStartUp		// �̓�����̋N����
	, ChargeBulletCharge	// �`���[�W�e�`���[�W
	, ChargeBulletFire		// �`���[�W�e����
	, ChargeBulletExplosion // �`���[�W�e����

	, Max
};

/*-------------------------------------
/* �T�E���h�Ǘ��N���X
-------------------------------------*/
class SoundManager
{
public:
	static const char* SoundTypeNames[static_cast<int>(SoundType::Max)];

public:
	SoundManager(class Game* game);
	~SoundManager(void);

	static SoundManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~

private:
	bool Init(void);	//������
	void Uninit(void);	//�I����

public:
	// ���ׂẴT�E���h���ꎞ��~
	void SetPausedToAllSound(bool isPaused);

	//�T�E���h�̃��[�g�p�X�̎擾
	std::string GetSoundRootpath(void) const { return sound_root_path_; }

	//�T�E���h�̓ǂݍ���
	class Sound* LoadSound(SoundType soundTypeID);

	//�T�E���h�̉��
	void ReleaseSound(SoundType soundTypeID);

	//��������������
	class Sound* FindSound(SoundType soundTypeID);

	//
	// �T�E���h�̒ǉ��ƍ폜
	//

	void AddSound(class Sound* sound);
	void RemoveSound(class Sound* sound);

	std::unordered_map<SoundType, std::string> GetSoundFilepathList(void) { return unmap_sound_path_list_; }

	class Game* GetGame(void) { return game_; }

	// XAudio2�̃C���^�[�t�F�C�X���擾
	IXAudio2* GetXAudio2Interface(void) { return xaudio2_; }

private:
	IXAudio2*				xaudio2_;					// XAudio2�ւ̃C���^�[�t�F�C�X

	IXAudio2MasteringVoice* xaudio2_mastering_voice_;	// �}�X�^�[�{�C�X

private:
	//�}�l�[�W���̏��L��
	class Game* game_;

	//�T�E���h�̃��[�g�p�X
	std::string sound_root_path_;

	//�T�E���h�̃p�X���X�g
	std::unordered_map<SoundType, std::string> unmap_sound_path_list_;

	//�T�E���h�̃R���e�i
	std::vector<class Sound*> sound_list_;

};

#endif //SOUND_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/