/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Shader.h] �V�F�[�_�[�̃x�[�X�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�V�F�[�_�[�̃x�[�X�N���X
=============================================================================*/
#ifndef SHADER_H_
#define	SHADER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "VertexData.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �V�F�[�_�[�N���X
-------------------------------------*/
class Shader
{
public:
	Shader(class ShaderManager* manager);
	virtual ~Shader(void);

	//���override�ł���悤��virtual��

	virtual bool Init(const LPDIRECT3DDEVICE9& lpd3d_device);	//������
	virtual void Uninit(void);	//�I����

	//�V�F�[�_�[�̃Z�b�g
	virtual void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Texture* texture);
	virtual void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Material* material);

	//�V�F�[�_�[�̊J�n
	virtual void ShaderPassBegin(int shaderPassNumber = 0);

	//�V�F�[�_�[�̏I��
	virtual void ShaderPassEnd(void);

private:
protected:
	//�V�F�[�_�[�̏��L��
	class ShaderManager* manager_;

	LPDIRECT3DVERTEXDECLARATION9 lpd3d_vertex_declaration_;	//���_�錾
	LPD3DXEFFECT				 shader_;					//�V�F�[�_���
};


#endif //RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/