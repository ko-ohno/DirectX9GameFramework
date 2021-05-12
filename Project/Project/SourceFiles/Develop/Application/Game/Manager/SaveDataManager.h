/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataManager.h] セーブデータ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：セーブデータ管理クラス
=============================================================================*/
#ifndef SAVE_DATA_MANAGER_H_
#define	SAVE_DATA_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

// スコアランクの定数データ
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

// スコアランクの上限値
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

// セーブデータクラス　
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
/* セーブデータ管理クラス
-------------------------------------*/
class SaveDataManager
{
public:
	SaveDataManager(class Game* game);
	~SaveDataManager(void);

	static SaveDataManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止	

private:
	bool Init(void);	 //初期化
	void Uninit(void);	 //終了化

private:
	// JSONファイルの作成
	void CreateNewJSONDataFile(const std::string& inFileName);

public:
	// JSONファイルの読み込みとセーブ
	bool LoadJSON(const std::string& inFileName);
	void SaveJSON(const std::string& inFileName);


public:
	class Game* GetGame(void) { return game_; }

	const std::vector<SaveData*>& GetSaveDataList(void) { return save_data_list_; }

	char ConvertToChar(ScoreRank scoreRank);

	// セーブデータの処理
	void CreateSaveData(int score);
	void AddSaveData(class SaveData* data);
	void RemoveSaveData(class SaveData* data);
	void SortBySaveData(void);

private:
	// マネージャーの所有者
	class Game* game_;

	// データのルートパス
	std::string data_file_root_path_;

	// データのファイルネーム
	std::string data_file_name_;

	// セーブデータの最大数
	static constexpr int MAX_SAVE_DATA_COUNT = 5;

	// セーブデータのコンテナ
	std::vector<SaveData*> save_data_list_;
};


#endif //SAVE_DATA_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/