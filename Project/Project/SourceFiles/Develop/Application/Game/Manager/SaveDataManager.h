/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataManager.h] �Z�[�u�f�[�^�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Z�[�u�f�[�^�Ǘ��N���X
=============================================================================*/
#ifndef SAVE_DATA_MANAGER_H_
#define	SAVE_DATA_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

// �X�R�A�����N�̒萔�f�[�^
enum class ScoreRank
{
	None = -1
	, S = 'S'
	, A = 'A'
	, B = 'B'
	, C = 'C'
	, D = 'D'
	, Max
};

// �Z�[�u�f�[�^�\����
struct SaveData
{
	int		  ranking_;
	int		  score_;
	ScoreRank score_rank_;
};


/*-------------------------------------
/* �Z�[�u�f�[�^�Ǘ��N���X
-------------------------------------*/
class SaveDataManager
{
public:
	SaveDataManager(class Game* game);
	~SaveDataManager(void);

	static SaveDataManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~	

private:
	bool Init(void);	 //������
	void Uninit(void);	 //�I����

private:
	// JSON�t�@�C���̍쐬
	void CreateNewJSONDataFile(const std::string& inFileName);

	// JSON�t�@�C���̓ǂݍ��݂ƃZ�[�u
public:
	bool LoadJSON(const std::string& inFileName);
	void SaveJSON(const std::string& inFileName);


public:
	class Game* GetGame(void) { return game_; }

	std::vector<SaveData> GetSaveDataList(void) { return save_data_list_; }

private:
	// �}�l�[�W���[�̏��L��
	class Game* game_;

	// �f�[�^�̃��[�g�p�X
	std::string data_file_root_path_;

	// �f�[�^�̃t�@�C���l�[��
	std::string data_file_name_;

	// �Z�[�u�f�[�^�̍ő吔
	static constexpr int MAX_SAVE_DATA_COUNT = 5;

	// �Z�[�u�f�[�^�̃R���e�i
	std::vector<SaveData> save_data_list_;
};


#endif //SAVE_DATA_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/