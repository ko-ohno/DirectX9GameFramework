/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataTest.cpp] �Z�[�u�f�[�^�e�X�g�p�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Z�[�u�f�[�^�e�X�g�p�Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "_SaveDataTest.h"
#include "../../Game.h"
#include "../../Manager/SaveDataManager.h"

#include "../../../ImGui/ImGuiManager.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SaveDataTest::SaveDataTest(Game* game)
	: GameObject(game)
{
	this->renderer_layer_type_ = RendererLayerType::Game;

}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SaveDataTest::~SaveDataTest(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
SaveDataTest* SaveDataTest::Create(Game* game)
{
	return NEW SaveDataTest(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SaveDataTest::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SaveDataTest::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void SaveDataTest::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void SaveDataTest::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	auto save_data_manager = game_->GetSaveDataManager();

	ImGui::Begin("SaveDataTest");
	// �Z�[�u
	{
		ImGui::Text("SaveData:");
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
		}
	}

	//�����[�h
	{
		ImGui::Text("SaveData:");
		ImGui::SameLine();
		if(ImGui::Button("Reload"))
		{
			save_data_manager->LoadJSON("Assets/SaveData/SaveData.json");
		}
	}

	//�����[�h
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