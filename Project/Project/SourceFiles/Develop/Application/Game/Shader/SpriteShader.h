/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.h] �X�v���C�g�V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�V�F�[�_�N���X
=============================================================================*/
#ifndef SPRITE_SHADER_H_
#define	SPRITE_SHADER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "Shader.h"

/*-------------------------------------
/* �\����
-------------------------------------*/
// ���_�f�[�^�t�H�[�}�b�g
typedef struct
{
	D3DXVECTOR3 position_;
	D3DCOLOR	d3d_color_;
	D3DXVECTOR2 texcoord_;
}CUSTOM_VERTEX;

// 2D�̒��_�t�H�[�}�b�g�̐ݒ�
#define FVF_CUSTOM_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1) 

/*-------------------------------------
/* �X�v���C�g�V�F�[�_�N���X
-------------------------------------*/
class SpriteShader : public Shader
{
public:
	SpriteShader(void);
	~SpriteShader(void);

	static SpriteShader* Create(void);

	bool Init(const LPDIRECT3DDEVICE9& lpd3d_device);
	void Uninit(void);

	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

	bool CreateVertexBuffer();
	bool CreateIndexBuffer();

	void Draw(const LPDIRECT3DDEVICE9& lpd3d_device);

	void SetCamera(class Camera* camera)
	{
		camera_ = camera;
	}

private:
	class Camera* camera_;

	D3DXMATRIX world_matrix_;		// �X�v���C�g�̃��[���h�ϊ��s��
	D3DXMATRIX view_matrix_;		// �J�����ϊ��s��
	D3DXMATRIX projection_matrix_;	// �v���W�F�N�V�����ϊ��s��

	static constexpr int MAX_VERTEX_COUNT = 4;
	CUSTOM_VERTEX vertex_array_[MAX_VERTEX_COUNT];

	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;	//���_�o�b�t�@
	//LPDIRECT3DINDEXBUFFER9  index_buffer_;

	LPDIRECT3DVERTEXSHADER9 vertex_shader_;					// ���_�V�F�[�_�[
	LPD3DXCONSTANTTABLE		vertexshader_constant_table_;	// �萔�e�[�u��

	LPDIRECT3DPIXELSHADER9	pixel_shader_;					// �s�N�Z���V�F�[�_�[
	LPD3DXCONSTANTTABLE		pixelshader_constant_table_;	// �萔�e�[�u��

	LPDIRECT3DTEXTURE9		texture_;

	LPDIRECT3DVERTEXDECLARATION9 lpd3d_vertex_declaration_;	//���_�錾
	LPD3DXEFFECT				 shader_;					//�V�F�[�_���

	D3DXHANDLE d3dxhandle_matrix_;	//���[���h�s��ւ̃n���h��
	D3DXHANDLE d3dxhandle_view_;	//�r���[�s��ւ̃n���h��
	D3DXHANDLE d3dxhandle_proj_;	//�v���W�F�N�V�����s��ւ̃n���h��

	D3DXHANDLE d3dxhandle_color_;	//���_�J���[�ւ̃n���h��
	D3DXHANDLE d3dxhandle_technique_;	//�e�N�j�b�N�ւ̃n���h��
	D3DXHANDLE d3dxhandle_texture_;	//�e�N�X�`���[�ւ̃n���h��
};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/