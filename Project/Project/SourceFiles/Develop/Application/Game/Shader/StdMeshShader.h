/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshShader.h] 標準メッシュシェーダー
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：標準メッシュシェーダクラス
=============================================================================*/
#ifndef STD_MESH_SHADER_H_
#define	STD_MESH_SHADER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "../Shader.h"

/*-------------------------------------
/* 標準メッシュシェーダー
-------------------------------------*/
class StdMeshShader : public Shader
{
public:
	StdMeshShader(class ShaderManager* manager);
	~StdMeshShader(void);

	bool Init(const LPDIRECT3DDEVICE9& lpd3d_device) override;
	void Uninit(void) override;

	//シェーダのコンパイル
	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);

private:
	bool NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

public:
	void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Texture* texture) override;

private:
	D3DXHANDLE d3dxhandle_technique_;	//テクニックへのハンドル
	D3DXHANDLE d3dxhandle_texture_;		//テクスチャーへのハンドル
};

#endif //STD_MESH_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/