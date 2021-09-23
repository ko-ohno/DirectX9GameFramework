/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteRendererComponent.h] �X�v���C�g�����_���[�R���|�[�l���g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�����_���[�R���|�[�l���g�N���X
=============================================================================*/
#ifndef SPRITE_RENDERER_H_
#define	SPRITE_RENDERER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �X�v���C�g�V�F�[�_�N���X
-------------------------------------*/
class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(class GameObject* owner, int drawOrder = 200);
	~SpriteRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::SpriteRendererComponent; };

private:
	//���_�p�o�b�t�@�쐬�֐��Q

	bool CreateVertexBuffer(void);
	bool CreateIndexBuffer(void);

	void ComputeVertexBuffer(void);

public:

	//UV���W�̌v�Z
	void SetUVAnimation(int textureCutX = 0, int textureCutY = 0, int textureCutWidth = 0, int textureCutHeight = 0)
	{
		//UV���W���v�Z���邩�̃t���O
		is_compute_texcord_ = true;

		//UV���W�̌v�Z
		texture_cut_x_ = textureCutX;
		texture_cut_y_ = textureCutY;
		texture_cut_width_  = textureCutWidth;
		texture_cut_height_ = textureCutHeight;
	}

	//�e�N�X�`���̐ݒ�
	void			SetTexture(TextureType textureTypeID);

	//�e�N�X�`���̎擾
	class Texture*	GetTexture();

	//�e�N�X�`�����̎擾
	D3DXIMAGE_INFO*	GetTextureImageInfo();

public:

	//�`����W���|���S���̒�����
	inline void IsSetDrawingPositionToCenter(const bool isOffsetScaleingCenter) { is_offset_scale_ = isOffsetScaleingCenter; }

	//��]�����̑���

	inline void SetRotate(float degree)
	{
		//��]���̗L����
		is_affine_ = true;

		//��]
		radian_	   = Math::ToRadian(degree);
	}

	inline void AddRotate(float addValueDegree)
	{
		//��]���̗L����
		is_affine_  = true;

		//��]
		radian_    += Math::ToRadian(addValueDegree);
	}

	inline float GetRadian(void) const { return radian_; }
	inline float GetDegree(void) const { return degree_; }

private:
	//�S�X�v���C�g���ʂ̒��_�p�̃f�[�^

	static constexpr int			MAX_VERTEX_COUNT = 4;	//���_�o�b�t�@��
	static LPDIRECT3DVERTEXBUFFER9	vertex_buffer_;			//���_�o�b�t�@

	static constexpr int			MAX_INDEX_COUNT = 6;	//�C���f�b�N�X�o�b�t�@
	static LPDIRECT3DINDEXBUFFER9	index_buffer_;			//�C���f�b�N�X�o�b�t�@��

	static VERTEX_STD*				vertex_buffer_address_;	//���_�o�b�t�@�̃A�h���X
	static LPWORD*					index_buffer_address_;	//�C���f�b�N�X�o�b�t�@�̃A�h���X

	//UV���W�v�Z�����邩�H
	bool is_compute_texcord_;

	//UV���W�̌v�Z�p

	int texture_cut_x_;
	int texture_cut_y_;
	int texture_cut_width_;
	int texture_cut_height_;

private:

	//�e�N�X�`���f�[�^
	class Texture* texture_;

private:
	//
	// �p������p�̃f�[�^
	//

	//��]�s��
	//�e�N���XRendererComponen�Œ�`����

	//���[���h�s��
	//�e�N���XRendererComponen�Œ�`����

	//�������W�ɃI�t�Z�b�g���邩
	bool is_offset_scale_;

	//���_���W���A�t�B���ϊ����邩
	bool is_affine_;

	//���W
	//�e�N���XRendererComponen�Œ�`����

	//�|���S���̃T�C�Y
	//�e�N���XRendererComponen�Œ�`����

	//��]�p�x
	float degree_;
	float radian_;
};

#endif //SPRITE_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/