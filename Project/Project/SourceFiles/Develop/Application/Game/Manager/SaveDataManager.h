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
	, S = 'S'
	, A = 'A'
	, B = 'B'
	, C = 'C'
	, D = 'D'
	, Max
};

// セーブデータ構造体
struct SaveData
{
	int		  ranking_;
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

	// JSONファイルの読み込みとセーブ
public:
	bool LoadJSON(const std::string& inFileName);
	void SaveJSON(const std::string& inFileName);


public:
	class Game* GetGame(void) { return game_; }

	std::vector<SaveData> GetSaveDataList(void) { return save_data_list_; }

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
	std::vector<SaveData> save_data_list_;
};


#endif //SAVE_DATA_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/