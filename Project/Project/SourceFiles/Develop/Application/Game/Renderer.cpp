/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Renderer.cpp] �����_���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_���[�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "Renderer.h"
#include "GameObjects/GameObject/Camera.h"
#include "GameObjects/Component/RendererComponent.h"

#include "Shader/DissolveShader.h"

#include "Shader/SpriteShader.h"

#include "Shader/BillboardShader.h"

#include "Shader/StdMeshShader.h"
#include "Shader/SkinMeshShader.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
Renderer::Renderer(Game* game)
	: game_(game)
	, shader_manager_(nullptr)
	, screen_width_(100)
	, screen_height_(100)
	, screen_scaler_(0.f)
	, now_camera_pos_(0.f, 0.f, 0.f)
	, old_camera_pos_(now_camera_pos_)
{

}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
Renderer::~Renderer(void)
{
	this->ShutDown();
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
Renderer* Renderer::Create(Game* game)
{
	return NEW Renderer(game);
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool Renderer::StartUp(void)
{
	//�J�����̃Q�[���I�u�W�F�N�g�̃R���e�i��������
	camera_game_objects_.clear();

	//�����_���[�R���|�[�l���g�̃R���e�i��������
	renderer_components_.clear();
	
	//�}�l�[�W���[
	{
		//�V�F�[�_�[�̃}�l�[�W���[�̎擾
		shader_manager_ = game_->GetShaderManager();
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void Renderer::ShutDown(void)
{
	//
	// ��`����K�v�Ȃ��B
	//
	// Game.cpp�̂ق��ŃQ�[���I�u�W�F�N�g���ꊇ�j�����Ă���̂�
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void Renderer::Update(void)
{

}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
void Renderer::Draw(void)
{
	//�����_���[�R���|�[�l���g�̕`��
	int now_draw_layer_order = 0;
	int camera_counter_ = 0;

	//��x����RendererLayerType��UI���C���[��Fade���C���[��`�悷��t���O
	bool is_2Dlayer_draw_one_time = false;
	
	//�`�惌�C���[���J��Ԃ�
	for (now_draw_layer_order
		;   now_draw_layer_order < static_cast<int>(RendererLayerType::Max)
		; ++now_draw_layer_order)
	{
		//�J�����̃C���X�^���X�������`�悷��
		for (auto camera_game_object : camera_game_objects_)
		{
		
			//RendererLayerType��UI���C���[��Fade���C���[��`�悷�邩�H
			is_2Dlayer_draw_one_time = ((camera_counter_ != 0)
										&& now_draw_layer_order >= static_cast<int>(RendererLayerType::UI));

			if (is_2Dlayer_draw_one_time)
			{
				continue;
			}

			//�����_���[�R���|�[�l���g�̃\�[�g
			const bool is_camera_moved = camera_game_object->IsGetCameraMoved();
			if (is_camera_moved == true)
			{
				D3DXVECTOR3 camera_position;
				D3DXMATRIX  view_matrix;

				//�r���[�s����t�s��ɂ��ăJ�������W�����o��
				{
					view_matrix = *camera_game_object->GetViewMatrix();;
					D3DXMatrixInverse(&view_matrix, nullptr, &view_matrix);

					camera_position.x = view_matrix._41;
					camera_position.y = view_matrix._42;
					camera_position.z = view_matrix._43;
				}

				for (auto renderer_component : renderer_components_)
				{
					auto rc_pos = *renderer_component->GetPosition();

					//�����_���[�R���|�[�l���g�ƃJ�����̋������v��
					auto dir = rc_pos - camera_position;
					auto vec_length = D3DXVec3Length(&dir);
					{
						//�J�����܂ł̋�����ݒ�@
						renderer_component->SetCameraDistance(vec_length);
					}
				}

				//�\�[�g���s��
				this->SortByRendererComponent();
			}

			//�����_���[�R���|�[�l���g�̕`�揈��
			this->DrawUpRendererComponents(camera_game_object, now_draw_layer_order);

			//���ڂ̃J�������H
			camera_counter_++;

		}
	}
}

/*-----------------------------------------------------------------------------
/* �����_���[�R���|�[�l���g�̕`�揈��
-----------------------------------------------------------------------------*/
void Renderer::DrawUpRendererComponents(Camera* camera, int nowDrawLayerOrder)
{
	//�R���|�[�l���g�̑��`��
	for (auto renderer_component : renderer_components_)
	{
		//�����_���[�̃��C���[�̏����擾
		auto renderer_layer_type = renderer_component->GetRendererLayerType();

		//�`�施�ߒ��̃��C���[�ƃ����_���[�̃��C���[�����������`��
		if (static_cast<int>(renderer_layer_type) == nowDrawLayerOrder)
		{
			//�V�F�[�_�[�̃Z�b�g
			auto shader_type = renderer_component->GetShaderType();
			if (shader_type == ShaderType::None)
			{
				assert(!"DrawUpRendererComponents():�s���ȃV�F�[�_�[���ݒ肳��Ă��܂��B");
			}

			auto shader = shader_manager_->ShaderDispatch(shader_type); //�萔�L�[����V�F�[�_���擾

			//�V�F�[�_���g�p�����R���|�[�l���g�̕`��
			renderer_component->Draw(shader, camera);
		}
	}
}

/*-----------------------------------------------------------------------------
/* �����_���[�R���|�[�l���g�̒ǉ�����
-----------------------------------------------------------------------------*/
void Renderer::AddRendererComponent(RendererComponent* rendererComponent)
{
	//�`��D�揇��
	RendererLayerType my_layer_type = rendererComponent->GetRendererLayerType();
	int				  my_draw_order = rendererComponent->GetDrawOrder();

	//�R���e�i���󂩂ǂ���
	auto iter = renderer_components_.begin();
	for (;
		iter != renderer_components_.end();
		++iter)
	{
		if (my_layer_type == (*iter)->GetRendererLayerType())
		{
			if (my_draw_order > (*iter)->GetDrawOrder())
			{
				break;
			}
		}
	}
	renderer_components_.insert(iter, rendererComponent);	//�}��
}

/*-----------------------------------------------------------------------------
/* �����_���[�ɃJ�����̃Q�[���I�u�W�F�N�g�̃|�C���^��ǉ�
-----------------------------------------------------------------------------*/
void Renderer::AddCameraGameObject(Camera* camera)
{
	camera_game_objects_.emplace_back(camera);
}

//
// �\�[�g�p�ɉ��Z�q���g��
//
//bool operator < (const RendererComponent& left, const RendererComponent& right)
//{
//	//�u���@> ��O�v�̏��ɕ`�悵�Ă����B
//	//�u���C���[�@> �`��D��x�@> �J���������v�̏��ɕ`�悵�Ă���
//	//�ȉ��̃\�[�g�̎菇�́A��r�����l�ǂ����̂����A�l��������(�D�揇�ʂ�����)�ق�����`�悵�Ă���
//	{
//		//��r�����l�ǂ������A�������C���[���������B
//		if (static_cast<int>(left.GetRendererLayerType())
//			== static_cast<int>(right.GetRendererLayerType()))
//		{
//			//��r�����l�ǂ������A�����`��D��x���������B
//			if (left.GetDrawOrder() == right.GetDrawOrder())
//			{
//				//��r�����l�ǂ������A�J��������
//				if (left.GetCameraDistance() < right.GetCameraDistance()) { return true; }
//			}
//			if (left.GetDrawOrder() < right.GetDrawOrder()) { return true; }
//		}
//
//		//��r�����l�ǂ������A�Ⴄ���C���[�������ꍇ�B
//		if (static_cast<int>(left.GetRendererLayerType())
//			< static_cast<int>(right.GetRendererLayerType()))
//		{
//			return true;
//		}
//	}
//	return false;
//}

/*-----------------------------------------------------------------------------
/* �����_���[�R���|�[�l���g�̃\�[�g����
-----------------------------------------------------------------------------*/
void Renderer::SortByRendererComponent(void)
{
	//�\�[�g�p�I�ʊ֐����g�p�����}�[�W�\�[�g
	std::stable_sort(
		renderer_components_.begin()
		, renderer_components_.end()
		, [](const RendererComponent* left, const RendererComponent* right)
		{
			if (static_cast<int>(left->GetRendererLayerType())
				== static_cast<int>(right->GetRendererLayerType()))
			{
 
				//��r�����l�ǂ������A�����`��D��x���������B
				if (left->GetDrawOrder() == right->GetDrawOrder())
				{
					//�J���������ɂ��\�[�g
					return left->GetCameraDistance() > right->GetCameraDistance();
				}
				else
				{
					//�`��I�[�_�[�ɂ��\�[�g
					return left->GetDrawOrder() < right->GetDrawOrder();
				}
			}
			else
			{
				//�`�惌�C���[�ɂ��\�[�g
				return static_cast<int>(left->GetRendererLayerType()) < static_cast<int>(right->GetRendererLayerType());
			}
		}
	);
}

/*=============================================================================
/*		End of File
=============================================================================*/