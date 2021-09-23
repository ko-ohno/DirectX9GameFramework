/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteDigitRendererComponent.h] �X�v���C�g�̌����`��R���|�[�l���g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�̌����`��R���|�[�l���g�N���X
=============================================================================*/
#ifndef SPRITE_DIGIT_RENDERER_H_
#define	SPRITE_DIGIT_RENDERER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"


/*-------------------------------------
/* �X�v���C�g�̌����`��R���|�[�l���g
-------------------------------------*/
class SpriteDigitRendererComponent : public RendererComponent
{
public:
	SpriteDigitRendererComponent(class GameObject* owner, int drawOrder = 200);
	~SpriteDigitRendererComponent(void);
	
private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::SpriteDigitRendererComponent; };

	// �e�N�X�`����ݒ肷��
	void SetTexture(TextureType textureType) { texture_type_ = textureType; };

	// ���̕`����W���|���S���̒��S�ɂ��邩
	void IsSetDrawingPositionToCenter(bool isIDrawingPositionToCenter) { is_drawing_position_to_center_ = isIDrawingPositionToCenter; }

	// �e�N�X�`���̐ݒ�@
	void IsSetFontTextureUVOriginZero(bool isTextureUVOriginZero) { is_font_texture_uv_origin_zero_ = isTextureUVOriginZero; }

	// �F���̐ݒ�
	void SetVertexColor(int red = 255, int green = 255, int blue = 255, int alpha = 255)
	{
		red_	= red;
		green_	= green;
		blue_	= blue;
		alpha_  = alpha;
	}

	// �`�悷��L�������̐ݒ�
	void SetDrawableDigitLength(int drawableDigitLength) { drawable_digit_length_ = (drawableDigitLength -1); };

	// �t�H���g�̕���ݒ�
	int GetFontWidth(void) { return font_width_; }
	void SetFontWidth(int width) { font_width_ = width; }

	// �t�H���g�̍�����ݒ�
	int GetFontHeight(void) { return font_height_; }
	void SetFontHeight(int height) { font_height_ = height; }

	// �����f�[�^�̐ݒ�
	void SetIntData(int data) { int_data_ = data; }

	// ���̊Ԃ̃I�t�Z�b�g�l��ݒ肷��
	int GetMaxDrawableDigitWidth(void) { return max_digit_width_; }

	// �I�t�Z�b�g�l��ݒ肷��
	void SetOffestWidth(int offsetWidth) { offset_width_ = offsetWidth; }


private:
	// �ő包��
	static constexpr int MAX_DIGIT_LENGTH = 8;

	//�e�N�X�`���̕�����
	static constexpr int texture_width_divisions = 5;
	static constexpr int texture_height_divisions = 2;

	// �\�����錅���̃X�v���C�g
	class SpriteRendererComponent* sprite_digit_[MAX_DIGIT_LENGTH];

	// �ݒ肷��e�N�X�`���̎��
	enum class TextureType texture_type_;

	// �`����W�𒆐S�ɂ��邩
	bool is_drawing_position_to_center_;

	// �t�H���g�e�N�X�`����UV���W�̌��_
	bool is_font_texture_uv_origin_zero_;

	//�F���
	int red_;
	int green_;
	int blue_;
	int alpha_;

	// �`�挅��
	int drawable_digit_length_;

	// �t�H���g�̕��ƍ���
	int font_width_;
	int font_height_;

	//�`�悷�錅�̍ő�̉���
	int max_digit_width_;

	// �������Ԃł̕����̃I�t�Z�b�g�l
	int offset_width_;

	// �����f�[�^
	int int_data_;
};

#endif //SPRITE_DIGIT_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/