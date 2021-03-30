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
/* �I��������
-----------------------------------------------------------------------------*/
void RendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//�������g�ƃJ�����܂ł̋������v������
	D3DXVECTOR3 camera_pos;
	D3DXVECTOR3 vector_length;
	
	//�����x�N�g����
	vector_length = this->position_ - camera_pos;
	camera_distance_ = D3DXVec3Length(&vector_length);
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void RendererComponent::Draw(class Shader* shader, class Camera* camera)
{
	UNREFERENCED_PARAMETER(shader);
}

/*=============================================================================
/*		End of File
=============================================================================*/