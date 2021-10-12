/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataTest.cpp] セーブデータテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：セーブデータテスト用ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "_SaveDataTest.h"
#include "../../../Game.h"
#include "../../../ResourceManager/SaveDataManager.h"

#include "../../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SaveDataTest::SaveDataTest(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SaveDataTest::~SaveDataTest(void)
{
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SaveDataTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SaveDataTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 入力処理
-----------------------------------------------------------------------------*/
void SaveDataTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SaveDataTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	auto save_data_manager = game_->GetSaveDataManager();

	auto save_data_list = save_data_manager->GetSaveDataList();

	ImGui::Begin("SaveDataTest");
	// セーブ
	{
		static char buf_score[256][5] = {};
		static char buf_score_rank[256][5] = {};

		int i = 0;
		for(auto save_data : save_data_list)
		{
			i++;
			std::string save_data_name = "save_data_" + std::to_string(i) + "_list";
			if (ImGui::TreeNode(save_data_name.c_str()))
			{
				ImGui::Text("score:%d", save_data->GetScore());
				ImGui::InputText("score", buf_score[i], sizeof(buf_score[i]));
				if (ImGui::Button("override1"))
				{
					int num = std::atoi(buf_score[i]);
					if (num >= 0.001)
					{
						save_data->SetScore(num);
					}
				}
				
				ImGui::Text("score_rank:%c", save_data_manager->ConvertToChar(save_data->GetScoreRank()));
				ImGui::InputText("score_rank", buf_score_rank[i], sizeof(buf_score_rank[i]));
				if (ImGui::Button("override2"))
				{
					//配列の0文字目を代入
					int num = buf_score_rank[0][i];
					save_data->SetScoreRank(static_cast<ScoreRank>(num));
				}

				ImGui::TreePop();
			}
		}
		
		ImGui::Text("SaveData:");
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			save_data_manager->SaveJSON("Assets/SaveData/SaveData.json");
		}
	}

	//リロード
	{
		ImGui::Text("SaveData:");
		ImGui::SameLine();
		if(ImGui::Button("Reload"))
		{
			save_data_manager->LoadJSON("Assets/SaveData/SaveData.json");
		}
	}

	// ソート
	{
		ImGui::Text("SaveData:");
		ImGui::SameLine();
		if (ImGui::Button("Sort"))
		{
			save_data_manager->SortBySaveData();
		}
	}
	ImGui::End();
}

/*=============================================================================
/*		End of File
=============================================================================*/