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
	D3DXVECTOR3 pos_;
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

	bool Init(class Camera* camera);
	void Uninit(void);

	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

	void Draw(const LPDIRECT3DDEVICE9& lpd3d_device);

private:
	//static constexpr int MAX_VERTEX_COUNT = 4;
	//CUSTOM_VERTEX vertex_array_[MAX_VERTEX_COUNT];

	//LPDIRECT3DVERTEXBUFFER9* vertex_buffer_;
	//LPDIRECT3DINDEXBUFFER9*  index_buffer_;

	LPDIRECT3DVERTEXSHADER9 vertex_shader_;		// ���_�V�F�[�_�[
	LPD3DXCONSTANTTABLE		vertexshader_constant_table_;	// �萔�e�[�u��

	LPDIRECT3DPIXELSHADER9	pixel_shader_;		// �s�N�Z���V�F�[�_�[
	LPD3DXCONSTANTTABLE		pixelshader_constant_table_;	// �萔�e�[�u��

	LPDIRECT3DTEXTURE9		texture_;


	D3DXMATRIX world_matrix_;		// �X�v���C�g�̃��[���h�ϊ��s��
	D3DXMATRIX view_matrix_;		// �J�����ϊ��s��
	D3DXMATRIX projection_matrix_;	// �v���W�F�N�V�����ϊ��s��
};


#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/