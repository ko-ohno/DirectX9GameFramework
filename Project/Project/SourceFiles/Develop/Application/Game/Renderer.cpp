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
#include "ResourceManager/EffectManager.h"

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
	, effect_manager_(nullptr)
	, effekseer_renderer_(nullptr)
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
	
	//�}�l�[�W���[�̎擾
	{
		//�V�F�[�_�[�̃}�l�[�W���[�̎擾
		this->shader_manager_ = game_->GetShaderManager();
		const bool shader_manager_init_failed = (shader_manager_ == nullptr);
		if (shader_manager_init_failed)
		{
			assert(!"Renderer::StartUp()�F�V�F�[�_�[�̃}�l�[�W���[�̎擾�Ɏ��s���܂����I");
			return false;
		}

		//�G�t�F�N�g�̃}�l�[�W���[�̎擾
		this->effect_manager_ = game_->GetEffectManager();
		const bool effect_manager_init_failed = (effect_manager_ == nullptr);
		if (effect_manager_init_failed)
		{
			assert(!"Renderer::StartUp()�F�G�t�F�N�g�̃}�l�[�W���[�̎擾�Ɏ��s���܂����I");
			return false;
		}

		//Effekseer�̕`�惌���_���[���擾
		this->effekseer_renderer_ = effect_manager_->GetEffekseerRenderer();
		const bool effekseer_renderer_init_failed = (effekseer_renderer_ == nullptr);
		if (effekseer_renderer_init_failed)
		{
			assert(!"Renderer::StartUp()�FEffekseer�̕`�惌���_���[�̎擾�Ɏ��s���܂����I");
			return false;
		}
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
				D3DXMATRIX  view_matrix = *camera_game_object->GetViewMatrix();
				D3DXMATRIX  projection_matrix = *camera_game_object->GetProjection3DMatrix();

				//�r���[�s����t�s��ɂ��ăJ�������W�����o��
				{
					//view_matrix = 
					D3DXMatrixInverse(&view_matrix, nullptr, &view_matrix);

					camera_position.x = view_matrix._41;
					camera_position.y = view_matrix._42;
					camera_position.z = view_matrix._43;
				}

				//�J�������W�ƕ`��I�u�W�F�N�g�̍��W�̋������v�Z
				for (auto renderer_component : renderer_components_)
				{
					auto rc_position = *renderer_component->GetPosition();

					//�����_���[�R���|�[�l���g�ƃJ�����̋������v��
					auto dir = rc_position - camera_position;
					auto vec_length = D3DXVec3Length(&dir);
					{
						//�J�����܂ł̋�����ݒ�@
						renderer_component->SetCameraDistance(vec_length);
					}
				}

				//�\�[�g���s��
				this->SortByRendererComponent();
			}

			//�G�t�F�N�g�̕`�惌�C���[�̎��ɕ`��
			if (now_draw_layer_order == static_cast<int>(RendererLayerType::ParticleEffect))
			{
				auto camera_matrix		= effect_manager_->Convert44Matrix(*camera_game_object->GetViewMatrix());
				auto projection_matrix	= effect_manager_->Convert44Matrix(*camera_game_object->GetProjection3DMatrix());
				{
					//	�J�����s��Ǝˉe�s���ϊ����ēn��
					effekseer_renderer_->SetCameraMatrix(camera_matrix);
					effekseer_renderer_->SetProjectionMatrix(projection_matrix);

					//Effekseer�̕`�惌���_���[�ɂ��EffectRendererComponent�̕`��
					effekseer_renderer_->BeginRendering();
					{
						//�����_���[�R���|�[�l���g�̕`�揈��
						this->DrawUpRendererComponents(camera_game_object, now_draw_layer_order);
					}
					effekseer_renderer_->EndRendering();
				}
			}
			else
			{
				//�����_���[�R���|�[�l���g�̕`�揈��
				this->DrawUpRendererComponents(camera_game_object, now_draw_layer_order);
			}

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
/* �����_���[�R���|�[�l���g�̃A�h���X�̒ǉ�����
-----------------------------------------------------------------------------*/
void Renderer::AddRendererComponentAddress(RendererComponent* rendererComponent)
{
	//�`��D�揇��
	RendererLayerType my_layer_type = rendererComponent->GetRendererLayerType();
	int				  my_draw_order = rendererComponent->GetDrawOrder();

	//�}���ł���܂ŃR���|�[�l���g�̌���
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
/* �����_���[�R���|�[�l���g�̃A�h���X�̍폜����
-----------------------------------------------------------------------------*/
void Renderer::RemoveRendererComponentAddress(RendererComponent* rendererComponent)
{
	auto iter = std::find(renderer_components_.begin()	//�͈�0�`
						 , renderer_components_.end()	//�͈͍ő�܂�
						 , rendererComponent);			//�T���Ώ�

	if (iter != renderer_components_.end())
	{
		renderer_components_.erase(iter);
	}
}

/*-----------------------------------------------------------------------------
/* �����_���[�ɃJ�����̃A�h���X�ǉ�����
-----------------------------------------------------------------------------*/
void Renderer::AddCameraGameObjectAddress(Camera* cameraGameObject)
{
	camera_game_objects_.emplace_back(cameraGameObject);
}

/*-----------------------------------------------------------------------------
/* �����_���[�̃J�����̃A�h���X�폜����
-----------------------------------------------------------------------------*/
void Renderer::RemoveCameraGameObjectAddress(Camera* cameraGameObject)
{
	auto iter = std::find(camera_game_objects_.begin()	//�͈�0�`
						 , camera_game_objects_.end()	//�͈͍ő�܂�
						 , cameraGameObject);			//�T���Ώ�

	if (iter != camera_game_objects_.end())
	{
		camera_game_objects_.erase(iter);
	}
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