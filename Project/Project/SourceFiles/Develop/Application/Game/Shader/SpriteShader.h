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
#include "../Shader.h"

/*-------------------------------------
/* �X�v���C�g�V�F�[�_�N���X
-------------------------------------*/
class SpriteShader : public Shader
{
public:
	SpriteShader(class ShaderManager* manager);
	~SpriteShader(void);

	//������
	bool Init(const LPDIRECT3DDEVICE9& lpd3d_device) override;

	//�V�F�[�_�̃R���p�C��
	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);

private:
	bool NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

public:
	void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Texture* texture) override;

private:
	D3DXHANDLE d3dxhandle_technique_;	//�e�N�j�b�N�ւ̃n���h��
	D3DXHANDLE d3dxhandle_texture_;		//�e�N�X�`���[�ւ̃n���h��
};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/