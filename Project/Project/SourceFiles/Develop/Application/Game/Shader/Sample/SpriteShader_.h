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
#include "../../../StdAfx.h"
#include "../Shader.h"

/*-------------------------------------
/* スプライトシェーダクラス
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
	D3DXMATRIX world_matrix_;		// スプライトのワールド変換行列
	D3DXMATRIX projection_matrix_;	// プロジェクション変換行列

	static constexpr int MAX_VERTEX_COUNT = 4;
	VERTEX_2D vertex_array_[MAX_VERTEX_COUNT];

	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;	//頂点バッファ
	LPDIRECT3DINDEXBUFFER9  index_buffer_;

	LPDIRECT3DTEXTURE9 texture_;

	D3DXHANDLE d3dxhandle_matrix_;	//ワールド行列へのハンドル
	D3DXHANDLE d3dxhandle_proj_;	//プロジェクション行列へのハンドル

	D3DXHANDLE d3dxhandle_color_;	//頂点カラーへのハンドル
	D3DXHANDLE d3dxhandle_technique_;	//テクニックへのハンドル
	D3DXHANDLE d3dxhandle_texture_;	//テクスチャーへのハンドル
};

#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/