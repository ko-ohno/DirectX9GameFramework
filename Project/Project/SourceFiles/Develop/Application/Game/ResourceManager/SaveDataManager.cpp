/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataManager.cpp] セーブデータ管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：セーブデータ管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "SaveDataManager.h"

//RapidJSONの利用
#include "JSONManager/JSONManager.h"
#include "JSONManager/JSONHelper.h"

static constexpr float data_version = 1.00f;

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SaveDataManager::SaveDataManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SaveDataManager::~SaveDataManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
SaveDataManager* SaveDataManager::Create(Game* game)
{
	return NEW SaveDataManager(game);
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool SaveDataManager::StartUp(void)
{
	//自身の初期化
	const bool collider_manager_init = this->Init();
	if (collider_manager_init == false)
	{
		assert(!"SaveDataManager::StartUp()：セーブデータマネージャの初期化に失敗しました。");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void SaveDataManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SaveDataManager::Init(void)
{
    // ファイルパスの場所を初期化
    data_file_root_path_ = "Assets/SaveData/";

    // ファイル名の設定
    data_file_name_ = "SaveData.json";

    // フルパスの作成
    auto file_path = data_file_root_path_ + data_file_name_;

	// セーブデータの読み込み
	{
        const bool is_load_failed = this->LoadJSON(file_path);
        if (is_load_failed == false)
        {
            std::string err_msg = "SaveDataManager::Init()：セーブデータの読み込みに失敗しました";
            MessageBox(nullptr, err_msg.c_str(), "警告", (MB_OK | MB_ICONWARNING));
            return false;
        }
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SaveDataManager::Uninit(void)
{
    // フルパスの作成
    auto file_path = data_file_root_path_ + data_file_name_;

    // セーブデータの作成
    {
        this->SaveJSON(file_path);
    }

    while (!save_data_list_.empty())
    {
        delete save_data_list_.back();
        save_data_list_.pop_back();
    }
}

/*-----------------------------------------------------------------------------
/* JSONのデータファイルの新規作成処理
-----------------------------------------------------------------------------*/
void SaveDataManager::CreateNewJSONDataFile(const std::string& inFileName)
{
    // セーブデータの初期化データ
    SaveData init_save_data[MAX_SAVE_DATA_COUNT] =
    {
        { static_cast<int>(ScoreRankLimits::S), ScoreRank::S },
        { static_cast<int>(ScoreRankLimits::A), ScoreRank::A },
        { static_cast<int>(ScoreRankLimits::B), ScoreRank::B },
        { static_cast<int>(ScoreRankLimits::C), ScoreRank::C },
        { static_cast<int>(ScoreRankLimits::D), ScoreRank::D }
    };

    // JSONファイルの出力
    {
        // JSONドキュメントのRootを宣言
        rapidjson::Document doc(rapidjson::kObjectType);
        {
            //Versionの記録
            const float version = data_version;
            {
                //バージョンのデータを先頭へ登録
                JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);
            }

            // セーブデータの作成
            for (int i = 0; i < MAX_SAVE_DATA_COUNT; i++)
            {
                auto save_data_name = "save_data_" + std::to_string(i+1);

                // セーブデータオブジェクトのバッファの作成
                rapidjson::Value save_data(rapidjson::kObjectType);
                {     
                    // スコアの入力
                    JSONHelper::AddInt(doc.GetAllocator(), save_data, "score", init_save_data[i].GetScore());

                    // スコアランクの入力
                    {
                        std::string score_rank;

                        switch (init_save_data[i].GetScoreRank())
                        {
                        case ScoreRank::S:
                            score_rank = "S";
                            break;

                        case ScoreRank::A:
                            score_rank = "A";
                            break;

                        case ScoreRank::B:
                            score_rank = "B";
                            break;

                        case ScoreRank::C:
                            score_rank = "C";
                            break;

                        case ScoreRank::D:
                            score_rank = "D";
                            break;

                        default:
                            assert(!"SaveDataManager::CreateNewJSONDataFile()：不正なスコアランクが指定されています！");
                            break;
                        }

                        JSONHelper::AddString(doc.GetAllocator(), save_data, "score_rank", score_rank);
                    }

                    // rapidjsonでのオブジェクト名の生成
                    rapidjson::Value rapidjson_object_data_name_;
                    {
                        rapidjson_object_data_name_.SetString(save_data_name.c_str(), doc.GetAllocator());
                    }

                    //セーブデータオブジェクトをメンバとして追加
                    doc.AddMember(rapidjson_object_data_name_, save_data, doc.GetAllocator());
                }
            }
        }

        // JSON用の文字列バッファを作成
        rapidjson::StringBuffer buffer;

        // 純粋な文字列バッファのアドレスを登録。文字列バッファをインデントされた状態へ変換できるように
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

        // ドキュメントの文字列バッファを構文解析。PrettyWriterによってインデントされた状態へ。
        doc.Accept(writer);

        // 変換された文字列バッファからデータを取得
        const char* output = buffer.GetString();

        // JSONファイルとして出力
        std::ofstream outFile(inFileName);
        if (outFile.is_open())
        {
            outFile << output;
        }
    }
}

/*-----------------------------------------------------------------------------
/* JSONの読み込み処理
-----------------------------------------------------------------------------*/
bool SaveDataManager::LoadJSON(const std::string& inFileName)
{
    // セーブデータのリストをクリア
    while (!save_data_list_.empty())
    {
        delete save_data_list_.back();
        save_data_list_.pop_back();
    }

    //JSONドキュメントオブジェクトのRootを生成
    rapidjson::Document doc(rapidjson::kObjectType);

    //JSONファイルの読み込み
    {
        const bool is_file_load_failed = JSONManager::LoadJSON(inFileName, doc);
        if (is_file_load_failed == false)
        {
            std::string err_msg = "セーブデータのファイル読み込みに失敗しました。\n";
            err_msg = err_msg + "セーブデータ用のファイルを新規作成します。\n";
            MessageBox(nullptr, err_msg.c_str(), "警告", (MB_OK | MB_ICONWARNING));

            //セーブデータファイルの新規作成
            {
                this->CreateNewJSONDataFile(inFileName);               
            }
            // 作成されたJSONファイルの読み込み
            JSONManager::LoadJSON(inFileName, doc);
        }

        // データの読み込み
        {
            //　バージョンの読み込み
            float version = 0.f;
            if (!JSONHelper::GetFloat(doc, "version", version)
                || version != data_version)
            {
                std::string err_msg = "セーブデータのversionが違いますが、このままシステムを実行します。\n";
                MessageBox(nullptr, err_msg.c_str(), "警告", (MB_OK | MB_ICONWARNING));
            }

            //　セーブデータの最大数まで読み込み
            for (int i = 0; i < MAX_SAVE_DATA_COUNT; i++)
            {
                std::string save_data_name = "save_data_" + std::to_string(i+1);

                // セーブデータオブジェクトの読み込み
                const rapidjson::Value& save_data = doc[save_data_name.c_str()];
                if (save_data.IsObject() == false)
                {
                    std::string err_msg = "セーブデータの情報が読み込めませんでした。\n";
                    err_msg = err_msg + "セーブデータ(" + std::to_string(i + 1) + ")：読み込みに失敗。";
                    MessageBox(nullptr, err_msg.c_str(), "警告", (MB_OK | MB_ICONWARNING));
                    return false;
                }

                // セーブデータ取得用バッファ
                int       score_data       = save_data["score"].GetInt();
                char      score_rank_data  = save_data["score_rank"].GetString()[0];

                //セーブデータにスコアランクの入力を行う
                ScoreRank input_score_rank = ScoreRank::None;
                {
                    switch (score_rank_data)
                    {
                    case 'S':
                        input_score_rank = ScoreRank::S;
                        break;

                    case 'A':
                        input_score_rank = ScoreRank::A;
                        break;

                    case 'B':
                        input_score_rank = ScoreRank::B;
                        break;

                    case 'C':
                        input_score_rank = ScoreRank::C;
                        break;

                    case 'D':
                        input_score_rank = ScoreRank::D;
                        break;

                    default:
                        std::string err_msg = "セーブデータのスコアランク情報に、不正な値が組み込まれています。\n";
                        MessageBox(nullptr, err_msg.c_str(), "警告", (MB_OK | MB_ICONWARNING));
                        break;
                    }
                }

                // セーブデータをリストに保存
                this->AddSaveData(NEW SaveData(score_data, input_score_rank));
            }
        }
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* JSONファイルへのセーブ処理
-----------------------------------------------------------------------------*/
void SaveDataManager::SaveJSON(const std::string& inFileName)
{
    // JSONドキュメントオブジェクトのRootを宣言
    rapidjson::Document doc(rapidjson::kObjectType);
    {
        //Versionの記録
        const float version = data_version;
        {
            //バージョンのデータを先頭へ登録
            JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);
        }

        //セーブデータのソート
        this->SortBySaveData();

        // セーブデータの作成
        int i = 0;
        for (auto save_data : save_data_list_)
        {
            i++;
            auto save_data_name = "save_data_" + std::to_string(i);

            // セーブデータオブジェクトのバッファの作成
            rapidjson::Value save_data_object(rapidjson::kObjectType);
            {
                // スコアの入力
                JSONHelper::AddInt(doc.GetAllocator(), save_data_object, "score", save_data->GetScore());

                // スコアランクの入力
                {
                    std::string score_rank;

                    switch (save_data->GetScoreRank())
                    {
                    case ScoreRank::S:
                        score_rank = "S";
                        break;

                    case ScoreRank::A:
                        score_rank = "A";
                        break;

                    case ScoreRank::B:
                        score_rank = "B";
                        break;

                    case ScoreRank::C:
                        score_rank = "C";
                        break;

                    case ScoreRank::D:
                        score_rank = "D";
                        break;

                    default:
                        assert(!"SaveDataManager::CreateNewJSONDataFile()：不正なスコアランクが指定されています！");
                        break;
                    }

                    JSONHelper::AddString(doc.GetAllocator(), save_data_object, "score_rank", score_rank);
                }

                // rapidjsonでのオブジェクト名の生成
                rapidjson::Value rapidjson_object_data_name_;
                {
                    rapidjson_object_data_name_.SetString(save_data_name.c_str(), doc.GetAllocator());
                }

                //セーブデータオブジェクトをメンバとして追加
                doc.AddMember(rapidjson_object_data_name_, save_data_object, doc.GetAllocator());
            }
        }
    }

    // ファイル出力
    {
        // JSON用の文字列バッファを作成
        rapidjson::StringBuffer buffer;

        // 純粋な文字列バッファのアドレスを登録。文字列バッファをインデントされた状態へ変換できるように
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

        // ドキュメントの文字列バッファを構文解析。PrettyWriterによってインデントされた状態へ。
        doc.Accept(writer);

        // 変換された文字列バッファからデータを取得
        const char* output = buffer.GetString();

        // JSONファイルとして出力
        std::ofstream outFile(inFileName);
        if (outFile.is_open())
        {
            outFile << output;
        }
    }
}

/*-----------------------------------------------------------------------------
/* スコアランクを文字へ変換する処理
-----------------------------------------------------------------------------*/
char SaveDataManager::ConvertToChar(ScoreRank scoreRank)
{
    char score_rank = '\0';

    switch (scoreRank)
    {
    case ScoreRank::S:
        score_rank = 'S';
        break;

    case ScoreRank::A:
        score_rank = 'A';
        break;

    case ScoreRank::B:
        score_rank = 'B';
        break;

    case ScoreRank::C:
        score_rank = 'C';
        break;

    case ScoreRank::D:
        score_rank = 'D';
        break;

    default:
        assert(!"SaveDataManager::ConvertToChar()：不正なスコアランクが指定されています！");
        break;
    }

    return score_rank;
}

/*-----------------------------------------------------------------------------
/* セーブデータの作成処理
-----------------------------------------------------------------------------*/
void SaveDataManager::AddNewSaveData(SaveData* data)
{
    //　新しいデータか？
    const bool is_new_date = data->IsGetNewData();
    if (is_new_date == false)
    {
        data->IsSetNewData(true);
    }

    // スコアランクのパラメータ
    ScoreRank score_rank = ScoreRank::None;

    // スコアの取得
    auto score = data->GetScore();

    // スコアのランクの設定
    {

        // ランクのスコア上限ランク
        int score_rank_limits[static_cast<int>(ScoreRankLimits::Max)] =
        {
            static_cast<int>(ScoreRankLimits::S),
            static_cast<int>(ScoreRankLimits::A),
            static_cast<int>(ScoreRankLimits::B),
            static_cast<int>(ScoreRankLimits::C),
            static_cast<int>(ScoreRankLimits::D)
        };

        // スコアランク配列
        ScoreRank score_rank_list[static_cast<int>(ScoreRank::Max)] =
        {
            ScoreRank::S,
            ScoreRank::A,
            ScoreRank::B,
            ScoreRank::C,
            ScoreRank::D
        };

        // スコアのランクを計算
        for (int i = 0; i < MAX_SAVE_DATA_COUNT; i++)
        {
            if (score >= static_cast<int>(score_rank_limits[i]))
            {
                score_rank = score_rank_list[i];
                break;
            }
        }
    }

    // スコアランクの更新
    data->SetScoreRank(score_rank);

    // セーブデータの追加処理
    this->AddSaveData(data);
}

/*-----------------------------------------------------------------------------
/* セーブデータの追加処理
-----------------------------------------------------------------------------*/
void SaveDataManager::AddSaveData(SaveData* data)
{
    //描画優先順位
    int	score = data->GetScore();

    //挿入できるまでコンポーネントの検索
    auto iter = save_data_list_.begin();
    for (;
        iter != save_data_list_.end();
        ++iter)
    {
        //　スコアが大きかったら
        if (score > (*iter)->GetScore())
        {
            break;
        }

        // スコアが同じだったら
        if (score == (*iter)->GetScore())
        {
            break;
        }
    }

    //データの挿入
    save_data_list_.insert(iter, data);	
}

/*-----------------------------------------------------------------------------
/* セーブデータの削除処理
-----------------------------------------------------------------------------*/
void SaveDataManager::RemoveSaveData(SaveData* data)
{
    auto iter = std::find(save_data_list_.begin()	//範囲0～
                         , save_data_list_.end()	//範囲最大まで
                         , data);			        //探す対象

    if (iter != save_data_list_.end())
    {
        save_data_list_.erase(iter);
    }
}

/*-----------------------------------------------------------------------------
/* JSONファイルへのセーブ処理
-----------------------------------------------------------------------------*/
void SaveDataManager::SortBySaveData(void)
{
    std::stable_sort(
        save_data_list_.begin()
        , save_data_list_.end()
        , [](const SaveData* left, const SaveData* right)
        {
            if (left->GetScore() == right->GetScore())
            {

                return left->GetScore() < right->GetScore();
            }
            else
            {
                return left->GetScore() > right->GetScore();
            }
        }
    );
}

/*=============================================================================
/*		End of File
=============================================================================*/