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
	, S
	, A
	, B
	, C
	, D
	, Max
};

// �X�R�A�����N�̏���l
enum class ScoreRankLimits
{
	None = -1
	, S = 4000
	, A = 3000
	, B = 2000
	, C = 1000
	, D =  500
	, Max
};

// �Z�[�u�f�[�^�N���X�@
class SaveData
{
public:
	SaveData(void)
		: score_(0)
		, score_rank_(ScoreRank::None)
	{}

	SaveData(int score, ScoreRank socreRank)
		: score_(score)
		, score_rank_(socreRank)
	{}

	SaveData(SaveData& data)
		: score_(data.score_)
		, score_rank_(data.score_rank_)
	{}

	~SaveData(void)
	{}

	inline int GetScore(void) const { return score_; }
	inline void SetScore(int score) { score_ = score; }

	inline ScoreRank GetScoreRank(void) const { return score_rank_; }
	inline void SetScoreRank(ScoreRank scoreRank) { score_rank_ = scoreRank; }

private:
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

public:
	// JSON�t�@�C���̓ǂݍ��݂ƃZ�[�u
	bool LoadJSON(const std::string& inFileName);
	void SaveJSON(const std::string& inFileName);


public:
	class Game* GetGame(void) { return game_; }

	const std::vector<SaveData*>& GetSaveDataList(void) { return save_data_list_; }

	char ConvertToChar(ScoreRank scoreRank);

	// �Z�[�u�f�[�^�̏���
	void CreateSaveData(int score);
	void AddSaveData(class SaveData* data);
	void RemoveSaveData(class SaveData* data);
	void SortBySaveData(void);

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
	std::vector<SaveData*> save_data_list_;
};


#endif //SAVE_DATA_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/