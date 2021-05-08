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
}

/*-----------------------------------------------------------------------------
/* JSONのデータファイルの新規作成処理
-----------------------------------------------------------------------------*/
void SaveDataManager::CreateNewJSONDataFile(const std::string& inFileName)
{
    // セーブデータの初期化データ
    SaveData init_save_data[MAX_SAVE_DATA_COUNT] = 
    {
        { 1, 4000, ScoreRank::S},
        { 2, 3000, ScoreRank::A},
        { 3, 2000, ScoreRank::B},
        { 4, 1000, ScoreRank::C},
        { 5,  500, ScoreRank::D}
    };

    //JSONファイルの出力
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
                    // ランキングの入力
                    JSONHelper::AddInt(doc.GetAllocator(), save_data, "ranking", init_save_data[i].ranking_);

                    // スコアの入力
                    JSONHelper::AddInt(doc.GetAllocator(), save_data, "score", init_save_data[i].score_);

                    // スコアランクの入力
                    {
                        std::string score_rank;

                        switch (init_save_data[i].score_rank_)
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
    save_data_list_.clear();

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
                SaveData save_data_buffer;

                // ランキングの読み込み
                save_data_buffer.ranking_ = save_data["ranking"].GetInt();

                // スコアの読み込み
                save_data_buffer.score_ = save_data["score"].GetInt();

                // スコアランクの読み込み
                std::string score_rank = save_data["score_rank"].GetString();

                // 文字を数値へ変換。ScoreRankと一致する文字を適用
                save_data_buffer.score_rank_ = static_cast<ScoreRank>(score_rank.at(0));

                //セーブデータにエラーが含まれているか
                bool is_error = false;
                {
                    switch (save_data_buffer.score_rank_)
                    {
                    case ScoreRank::None:
                        is_error = true;
                        break;

                    case ScoreRank::S:
                        break;

                    case ScoreRank::A:
                        break;

                    case ScoreRank::B:
                        break;

                    case ScoreRank::C:
                        break;

                    case ScoreRank::D:
                        break;

                    case ScoreRank::Max:
                        is_error = true;
                        break;

                    default:
                        is_error = true;
                        break;
                    }

                    if (is_error)
                    {
                        std::string err_msg = "セーブデータのスコアランク情報に、不正な値が組み込まれています。\n";
                        MessageBox(nullptr, err_msg.c_str(), "警告", (MB_OK | MB_ICONWARNING));
                    }
                }

                // セーブデータをリストに保存
                save_data_list_.emplace_back(save_data_buffer);
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
    //// JSONドキュメントのRootを宣言
    //rapidjson::Document doc(rapidjson::kObjectType);
    //{
    //    //Versionの記録
    //    const float version = data_version;
    //    {
    //        //バージョンのデータを先頭へ登録
    //        JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);
    //    }

    //    //プロパティオブジェクトのバッファの作成
    //    rapidjson::Value property(rapidjson::kObjectType);
    //    {
    //        //プロパティオブジェクトの生成
    //        this->SaveProperties(doc.GetAllocator(), property);

    //        //プロパティオブジェクトをメンバとして追加
    //        doc.AddMember("Properties", property, doc.GetAllocator());
    //    }
    //}

    //// JSON用の文字列バッファを作成
    //rapidjson::StringBuffer buffer;

    //// 純粋な文字列バッファのアドレスを登録。文字列バッファをインデントされた状態へ変換できるように
    //rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    //// ドキュメントの文字列バッファを構文解析。PrettyWriterによってインデントされた状態へ。
    //doc.Accept(writer);

    //// 変換された文字列バッファからデータを取得
    //const char* output = buffer.GetString();

    //// JSONファイルとして出力
    //std::ofstream outFile(inFileName);
    //if (outFile.is_open())
    //{
    //    outFile << output;
    //}
}

/*=============================================================================
/*		End of File
=============================================================================*/