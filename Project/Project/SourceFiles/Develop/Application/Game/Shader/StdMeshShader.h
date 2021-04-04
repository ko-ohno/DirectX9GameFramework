/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshShader.h] �W�����b�V���V�F�[�_�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�W�����b�V���V�F�[�_�N���X
=============================================================================*/
#ifndef STD_MESH_SHADER_H_
#define	STD_MESH_SHADER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../Shader.h"

/*-------------------------------------
/* �W�����b�V���V�F�[�_�[
-------------------------------------*/
class StdMeshShader : public Shader
{
public:
	StdMeshShader(class ShaderManager* manager);
	~StdMeshShader(void);

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

	D3DXHANDLE d3dxhandle_pos_;			//�ʒu���ւ̃n���h��
	D3DXHANDLE d3dxhandle_scale_;		//�g�k���ւ̃n���h��
	D3DXHANDLE d3dxhandle_view_;		//�r���[�s��ւ̃n���h��
	D3DXHANDLE d3dxhandle_projection_;	//�v���W�F�N�V�������ւ̃n���h��

};

#endif //STD_MESH_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/