/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.h] スプライトシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダクラス
=============================================================================*/
#ifndef SPRITE_SHADER_H_
#define	SPRITE_SHADER_H_

/*--- インクルードファイル ---*/
#include "../Shader.h"

/*-------------------------------------
/* スプライトシェーダクラス
-------------------------------------*/
class SpriteShader : public Shader
{
public:
	SpriteShader(class ShaderManager* manager);
	~SpriteShader(void);

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
};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/