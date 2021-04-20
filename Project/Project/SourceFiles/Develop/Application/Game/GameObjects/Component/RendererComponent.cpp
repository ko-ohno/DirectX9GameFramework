/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[RendererComponent.cpp] �����_�����O�R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_�����O�R���|�[�l���g�ɋ��ʂ��鏈���̒�`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"	
#include "RendererComponent.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "../../Game.h"
#include "../../../Math.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
RendererComponent::RendererComponent(GameObject* owner, int drawOrder)
	: Component(owner, drawOrder)
	, draw_order_(drawOrder)
	, renderer_layer_type_(RendererLayerType::None)
	, shader_type_(ShaderType::None)
	, camera_distance_(0.f)
	, vertex_color_(D3DCOLOR_RGBA(255, 255, 255, 255))
	, position_(0.f, 0.f, 0.f)
	, scale_(1.f, 1.f, 1.f)
{
	//�R���|�[�l���g�̏��L�҂̕`�惌�C���[���擾
	renderer_layer_type_ = owner->GetRendererLayerType();

	//�s��̏�����
	D3DXMatrixIdentity(&rotation_matrix_);
	D3DXMatrixIdentity(&world_matrix_);

	//���L�҂��s���ȃQ�[���I�u�W�F�N�g����Ȃ������ׂ�
	if (renderer_layer_type_ == RendererLayerType::None)
	{
		assert(!"�Q�[���I�u�W�F�N�g�̃��C���[���I������Ă��܂���I");
	}

	owner_->GetGame()->GetRenderer()->AddRendererComponent(this);
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
RendererComponent::~RendererComponent(void)
{
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool RendererComponent::Init(void)
{
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void RendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void RendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//��]���
	D3DXMATRIX rotation_matrix = this->rotation_matrix_;

	//�ʒu���A�g�k���
	D3DXVECTOR3 position = this->position_;
	D3DXVECTOR3 scale = this->scale_;

	//�g�k�̃x�N�g���l�ɁA��]�s��̒l�����킦�Čv�Z

	//X��
	world_matrix_._11 = scale.x * rotation_matrix._11;
	world_matrix_._12 = scale.x * rotation_matrix._12;
	world_matrix_._13 = scale.x * rotation_matrix._13;

	//Y��
	world_matrix_._21 = scale.y * rotation_matrix._21;
	world_matrix_._22 = scale.y * rotation_matrix._22;
	world_matrix_._23 = scale.y * rotation_matrix._23;

	//Z��
	world_matrix_._31 = scale.z * rotation_matrix._31;
	world_matrix_._32 = scale.z * rotation_matrix._32;
	world_matrix_._33 = scale.z * rotation_matrix._33;

	//���s�ړ�
	world_matrix_._41 = position.x;
	world_matrix_._42 = position.y;
	world_matrix_._43 = position.z;

	//W����
	world_matrix_._14 = world_matrix_._24 = world_matrix_._34 = 0.0f;

	//1.0f�ɐݒ肷�邱�Ƃ�world_matrix_._4*���x�N�g����
	world_matrix_._44 = 1.0f;
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void RendererComponent::Draw(class Shader* shader, class Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
	UNREFERENCED_PARAMETER(camera);
}

/*=============================================================================
/*		End of File
=============================================================================*/