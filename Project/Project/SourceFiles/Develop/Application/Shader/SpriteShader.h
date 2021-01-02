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
#include "Shader.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/
// 頂点データフォーマット
typedef struct
{
	D3DXVECTOR3 pos_;
	D3DCOLOR	d3d_color_;
	D3DXVECTOR2 texcoord_;
}CUSTOM_VERTEX;

// 2Dの頂点フォーマットの設定
#define FVF_CUSTOM_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*-------------------------------------
/* スプライトシェーダクラス
-------------------------------------*/
class SpriteShader : public Shader
{
public:
	SpriteShader(void);
	~SpriteShader(void);

	static SpriteShader* Create(void);

	bool Init(class Camera* camera);
	void Uninit(void);

	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

	void Draw(const LPDIRECT3DDEVICE9& lpd3d_device);

private:
	//static constexpr int MAX_VERTEX_COUNT = 4;
	//CUSTOM_VERTEX vertex_array_[MAX_VERTEX_COUNT];

	//LPDIRECT3DVERTEXBUFFER9* vertex_buffer_;
	//LPDIRECT3DINDEXBUFFER9*  index_buffer_;

	LPDIRECT3DVERTEXSHADER9 vertex_shader_;		// 頂点シェーダー
	LPD3DXCONSTANTTABLE		vertexshader_constant_table_;	// 定数テーブル

	LPDIRECT3DPIXELSHADER9	pixel_shader_;		// ピクセルシェーダー
	LPD3DXCONSTANTTABLE		pixelshader_constant_table_;	// 定数テーブル

	LPDIRECT3DTEXTURE9		texture_;


	D3DXMATRIX world_matrix_;		// スプライトのワールド変換行列
	D3DXMATRIX view_matrix_;		// カメラ変換行列
	D3DXMATRIX projection_matrix_;	// プロジェクション変換行列
};


#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/