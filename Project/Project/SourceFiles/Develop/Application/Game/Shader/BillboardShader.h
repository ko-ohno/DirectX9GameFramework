/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardShader.h] �r���{�[�h�V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�r���{�[�h�V�F�[�_�N���X
=============================================================================*/
#ifndef BILLBOARD_SHADER_H_
#define	BILLBOARD_SHADER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Shader.h"

/*-------------------------------------
/* �r���{�[�h�V�F�[�_�N���X
-------------------------------------*/
class BillboardShader : public Shader
{
public:
	BillboardShader(class ShaderManager* manager);
	~BillboardShader(void);

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

	D3DXHANDLE d3dxhandle_pos_;				//�ʒu���ւ̃n���h��
	D3DXHANDLE d3dxhandle_scale_;			//�g�k���ւ̃n���h��
	D3DXHANDLE d3dxhandle_view_inverse_;	//�t�r���[�s��ւ̃n���h��
	D3DXHANDLE d3dxhandle_view_;			//�r���[�s��ւ̃n���h��
	D3DXHANDLE d3dxhandle_projection_;		//�ւ̃n���h��

};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/

