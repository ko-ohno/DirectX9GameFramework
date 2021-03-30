/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardShader.h] ビルボードシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ビルボードシェーダクラス
=============================================================================*/
#ifndef BILLBOARD_SHADER_H_
#define	BILLBOARD_SHADER_H_

/*--- インクルードファイル ---*/
#include "../Shader.h"

/*-------------------------------------
/* ビルボードシェーダクラス
-------------------------------------*/
class BillboardShader : public Shader
{
public:
	BillboardShader(class ShaderManager* manager);
	~BillboardShader(void);

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

	D3DXHANDLE d3dxhandle_pos_;				//位置情報へのハンドル
	D3DXHANDLE d3dxhandle_scale_;			//拡縮情報へのハンドル
	D3DXHANDLE d3dxhandle_view_inverse_;	//逆ビュー行列へのハンドル
	D3DXHANDLE d3dxhandle_view_;			//ビュー行列へのハンドル
	D3DXHANDLE d3dxhandle_projection_;		//へのハンドル

};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/

