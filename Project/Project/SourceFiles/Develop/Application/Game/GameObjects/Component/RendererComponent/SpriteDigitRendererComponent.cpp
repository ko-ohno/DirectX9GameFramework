/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteDigitRendererComponent.cpp] �X�v���C�g�̌����`��R���|�[�l���g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�̌����`��R���|�[�l���g�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../StdAfx.h"
#include "SpriteDigitRendererComponent.h"
#include "SpriteRendererComponent.h"
#include "../../GameObject.h"

/*---------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SpriteDigitRendererComponent::SpriteDigitRendererComponent(class GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, texture_type_(TextureType::None)
	, is_drawing_position_to_center_(false)
	, is_font_texture_uv_origin_zero_(false)
	, red_(255)
	, green_(255)
	, blue_(255)
	, alpha_(255)
	, font_width_(0)
	, font_height_(0)
	, max_digit_width_(0)
	, offset_width_(0)
	, drawable_digit_length_(0)
	, int_data_(0)
{
	const bool is_init_sprite_digit_renderer = this->Init();
	if (is_init_sprite_digit_renderer == false)
	{
		assert(!"�X�v���C�g�̌��������_���[�̏������Ɏ��s����");
	}
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SpriteDigitRendererComponent::~SpriteDigitRendererComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SpriteDigitRendererComponent::Init(void)
{
	//�`��V�F�[�_�[�̎w��
	this->shader_type_ = ShaderType::Sprite;

	// ������
	{
		//�I�t�Z�b�g�����悱���̒l
		offset_width_ = 25;

		// ���̕��ƍ���
		font_width_			   =  90;
		font_height_		   = 100;

		// �`�悷�錅�����̒���
		drawable_digit_length_ = 8;

		// �����f�[�^
		int_data_ = 0;
	}

	// �����`��R���|�[�l���g�̏�����
	{
		for (int i = 0; i < MAX_DIGIT_LENGTH; i++)
		{
			// �C���X�^���X����
			sprite_digit_[i] = NEW SpriteRendererComponent(owner_);
			sprite_digit_[i]->SetScaleX(static_cast<float>(font_width_));
			sprite_digit_[i]->SetScaleY(static_cast<float>(font_height_));

			// �`�悷�邩�̐ݒ�
			if (i <= drawable_digit_length_ -1)
			{
				sprite_digit_[i]->IsSetDrawable(false);
			}
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SpriteDigitRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �X�V����
-----------------------------------------------------------------------------*/
void SpriteDigitRendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// �G���[�`�F�b�N
	{
		// �`�悷�錅�����ő�������Ă�����
		if (drawable_digit_length_ >= MAX_DIGIT_LENGTH)
		{
			assert(!"SpriteDigitRendererComponent::Update():�`�悷�錅�����ő�F8�������Ă��܂��I");
		}

		// �e�N�X�`�����ݒ肳��Ă��邩
		if (texture_type_ == TextureType::None)
		{
			assert(!"SpriteDigitRendererComponent::Update():�e�N�X�`�����ݒ肳��Ă��܂���I");
		}

	}

	// �e�N�X�`������ݒ�
	for (int i = 0; i < MAX_DIGIT_LENGTH; i++)
	{
		sprite_digit_[i]->SetTexture(texture_type_);
	}

	// ���̒�������[�܂ł̉���
	const float digit_center_width = (font_width_ * drawable_digit_length_) / 2.f;


	// �e�N�X�`���̕��ƍ���
	const int texture_width = sprite_digit_[0]->GetTextureImageInfo()->Width;
	const int texture_height = sprite_digit_[0]->GetTextureImageInfo()->Height ;

	// �e�N�X�`���̐؂���T�C�Y
	const int texture_cut_width = (texture_width / texture_width_divisions);
	const int texture_cut_height = (texture_height / texture_height_divisions);
	

	// ���l�̌v�Z
	int draw_digit_value = 0;

	//�{��
	int magnification = 10; //score��10^N(�ݏ�)�Ŋ��邽�߂̕ϐ��B

	//�]��̔{��
	int surplus_magnification = 1; //n���ڂ̒l���������]�肩��v�Z����ϐ�

	// �����̍X�V
	for (int i = 0; i < MAX_DIGIT_LENGTH; i++)
	{
		// �`�悷�邩��ݒ肷��
		if (i <= drawable_digit_length_ - 1)
		{
			sprite_digit_[i]->IsSetDrawable(true);
		}
		else
		{
			sprite_digit_[i]->IsSetDrawable(false);
		}

		// �`�悵�Ȃ�������X�V���Ȃ�
		if (sprite_digit_[i]->IsGetDrawable() == false)
		{
			break;
		}

		// ���l�̌v�Z
		{
			//���̗]��̌v�Z
			draw_digit_value = int_data_ % magnification;	//score_��magnification�̂����Ŋ������]���������B
			draw_digit_value /= surplus_magnification;		//score_(�������]��)��surplus_magnification�Ŋ��ꂽ����������B
		}

		// �g�k���̍X�V
		{
			sprite_digit_[i]->SetScaleX(static_cast<float>(font_width_));
			sprite_digit_[i]->SetScaleY(static_cast<float>(font_height_));
			sprite_digit_[i]->IsSetDrawingPositionToCenter(is_drawing_position_to_center_);
		}

		// �|���S���J���[�̍X�V
		{
			sprite_digit_[i]->SetVertexColor(red_, green_, blue_, alpha_);
		}

		// UV���W�̌v�Z
		{
			//int draw_digit_value = i;

			if (is_font_texture_uv_origin_zero_ == true)
			{
				//value��0�̎��A�e�N�X�`����UV���W�𐔎���"0"������ʒu�܂ł����Ă����B
				if (draw_digit_value == 0)
				{
					draw_digit_value = 9; //"0"������UV���W�̔ԍ�
				}
				else
				{
					draw_digit_value -= 1; //�ŏ��ɐ�����"0"���Ȃ�������1�������B
				}
			}

			sprite_digit_[i]->SetUVAnimation(texture_cut_width * (draw_digit_value % 5)
											, texture_cut_height * (draw_digit_value / 5)
											, texture_cut_width
											, texture_cut_height);
		}

		// �`����W�̌v�Z
		{
			// �t�H���g�Ԃ̍s��
			const int font_padding_width = font_width_ - offset_width_;

			// �e���̕�
			max_digit_width_ = font_padding_width * drawable_digit_length_;

			// �S�̂̒�����������Ă���
			const float draw_pos_x = position_.x + (max_digit_width_ - (font_padding_width * (i + 1)));
			const float draw_pos_y = position_.y;

			// ���W�̐ݒ�
			sprite_digit_[i]->SetTranslationX(draw_pos_x);
			sprite_digit_[i]->SetTranslationY(draw_pos_y);
		}

		// ���l�̌v�Z
		{
			//�Ō�ɂ��ꂼ��10�{�ɂ��āA���̈ʂ֌����J��グ��B
			magnification *= 10;
			surplus_magnification *= 10;
		}
	}
}

/*-----------------------------------------------------------------------------
/* �`�揈��
-----------------------------------------------------------------------------*/
//void SpriteDigitRendererComponent::Draw(Shader* shader, Camera* camera)
//{
//		SpriteRendererComponent���g�p���Ă���̂ŕ`�揈���͕K�v�Ȃ�
//}

/*=============================================================================
/*		End of File
=============================================================================*/