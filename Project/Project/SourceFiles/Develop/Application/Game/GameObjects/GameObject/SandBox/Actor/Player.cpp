/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Player.cpp] �v���C���[�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�v���C���[�̏������`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../StdAfx.h"
#include "Player.h"
#include "../../../Component/RendererComponent/FFPMeshRendererComponent.h"
#include "../../../Component/RendererComponent/EffectRendererComponent.h"
#include "../../../Component/TransformComponent.h"

#include "../../../../../ImGui/ImGuiManager.h"
#include "../../../../Input/InputCheck.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Player::Player(Game* game)
	: Actor(game)
	, mesh_space_ship_(nullptr)
	, effect_after_burner_(nullptr)
{
	mesh_space_ship_ = NEW FFPMeshRendererComponent(this);
	mesh_space_ship_->SetMesh(XFileMeshType::SpaceShip);
	mesh_space_ship_->SetEnableLighting(true);
	mesh_space_ship_->SetScale(0.5f);

	test_mesh_ = NEW FFPMeshRendererComponent(this);
	test_mesh_->SetMesh(XFileMeshType::GreenBullet);
	test_mesh_->SetTranslationX(5.f);

	effect_after_burner_ = NEW EffectRendererComponent(this);
	effect_after_burner_->SetEffect(EffectType::AfterBurner);
	effect_after_burner_->Play();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Player::~Player(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Player::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Player::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* ���͏���
-----------------------------------------------------------------------------*/
void Player::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Player::UpdateGameObject(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//D3DXVECTOR3 position;
	//D3DXVECTOR3 src_position = { 0.f,  0.f, -150.f };
	//D3DXVECTOR3 tgt_position = { 0.f,  0.f,    0.f };

	//static float time = 0.f;
	//static bool is_moving  = false;

	//ImGui::Begin("time");
	//ImGui::Text("time:%f", time);
	//ImGui::End();

	//if (InputCheck::KeyPress(DIK_SPACE))
	//{
	//	time += deltaTime/10;
	//}

	//if (time >= 1.f)
	//{
	//	is_moving = true;
	//	time = 1.f;
	//}

	//D3DXVec3Lerp(&position, &src_position, &tgt_position, time);
	//
	//mesh_space_ship_->SetTranslation(position);

	//transform_component_->SetTranslation();

	static float player_rotY_value = 0.f;
	ImGui::Begin("Player");
	ImGui::Text("PlayerRotValue:%f", player_rotY_value);
	ImGui::SliderFloat("##player_rot_bar", &player_rotY_value, 0.0f, 360.0f);
	ImGui::Text("transform_deg_:%f", transform_component_->GetAngleYaw());
	ImGui::End();

	transform_component_->IsSetExecuteSlerp(true);
	this->transform_component_->SetRotationYaw(player_rotY_value);


	//D3DXMATRIX rot;
	//static float rot_val = 0;
	//rot_val += deltaTime;
	//D3DXMatrixRotationY(&rot, rot_val);


	//mesh_space_ship_->SetRotationMatrix(rot);
	effect_after_burner_->SetTranslation(0.f, 0.1f, -1.1f);
}

/*=============================================================================
/*		End of File
=============================================================================*/