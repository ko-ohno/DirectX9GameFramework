/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshShader.h] 標準メッシュシェーダクラス
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

	//初期化
	bool Init(const LPDIRECT3DDEVICE9& lpd3d_device) override;

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

	D3DXHANDLE d3dxhandle_pos_;			//位置情報へのハンドル
	D3DXHANDLE d3dxhandle_scale_;		//拡縮情報へのハンドル
	D3DXHANDLE d3dxhandle_view_;		//ビュー行列へのハンドル
	D3DXHANDLE d3dxhandle_projection_;	//プロジェクション情報へのハンドル

};

#endif //STD_MESH_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/