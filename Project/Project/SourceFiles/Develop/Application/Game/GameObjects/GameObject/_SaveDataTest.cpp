/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataTest.cpp] セーブデータテスト用ゲームオブジェクト
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：セーブデータテスト用ゲームオブジェクト
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "_SaveDataTest.h"
#include "../../Game.h"
#include "../../Manager/SaveDataManager.h"

#include "../../../ImGui/ImGuiManager.h"

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
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
SaveDataTest* SaveDataTest::Create(Game* game)
{
	return NEW SaveDataTest(game);
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

	ImGui::Begin("SaveDataTest");
	// セーブ
	{
		ImGui::Text("SaveData:");
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
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

	//リロード
	{
		ImGui::Text("PrintOut");
		
		auto save_data_list = game_->GetSaveDataManager()->GetSaveDataList();

		int i = 0;
		for (auto iter = save_data_list.begin()
			; iter != save_data_list.end()
			; ++iter)
		{
			i++;
			std::string save_data_name = "save_data_" + std::to_string(i);
			if (ImGui::TreeNode(save_data_name.c_str()))
			{
				ImGui::Text("ranking:%d", iter->ranking_);
				ImGui::Text("score:%d", iter->score_);
				ImGui::Text("score_rank:%c", iter->score_rank_);
				ImGui::TreePop();
			}
		}
	}

	ImGui::End();

}

/*=============================================================================
/*		End of File
=============================================================================*/