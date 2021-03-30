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
#include "../../../StdAfx.h"
#include "../Shader.h"

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

private:
	D3DXMATRIX world_matrix_;		// �X�v���C�g�̃��[���h�ϊ��s��
	D3DXMATRIX projection_matrix_;	// �v���W�F�N�V�����ϊ��s��

	static constexpr int MAX_VERTEX_COUNT = 4;
	VERTEX_2D vertex_array_[MAX_VERTEX_COUNT];

	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9  index_buffer_;

	LPDIRECT3DTEXTURE9 texture_;

	D3DXHANDLE d3dxhandle_matrix_;	//���[���h�s��ւ̃n���h��
	D3DXHANDLE d3dxhandle_proj_;	//�v���W�F�N�V�����s��ւ̃n���h��

	D3DXHANDLE d3dxhandle_color_;	//���_�J���[�ւ̃n���h��
	D3DXHANDLE d3dxhandle_technique_;	//�e�N�j�b�N�ւ̃n���h��
	D3DXHANDLE d3dxhandle_texture_;	//�e�N�X�`���[�ւ̃n���h��
};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/