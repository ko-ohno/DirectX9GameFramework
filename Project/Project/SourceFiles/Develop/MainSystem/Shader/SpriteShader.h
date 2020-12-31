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
#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*-------------------------------------
/* スプライトシェーダクラス
-------------------------------------*/
class SpriteShader
{
public:
	SpriteShader(void);
	~SpriteShader(void);

	static SpriteShader* Create(void);

	void Init(void);
	void Uninit(void);

	bool ShaderCompile(LPDIRECT3DDEVICE9 device);

	void Draw();

private:
	static constexpr int MAX_VERTEX_NUM = 4;
	CUSTOM_VERTEX vertex_array_[MAX_VERTEX_NUM];

	LPDIRECT3DVERTEXSHADER9 vertex_shader_;		// 頂点シェーダー
	LPD3DXCONSTANTTABLE		vs_constant_table_;	// 定数テーブル

	LPDIRECT3DPIXELSHADER9	pixel_shader_;		// ピクセルシェーダー
	LPD3DXCONSTANTTABLE		ps_constant_table_;	// 定数テーブル

	LPDIRECT3DTEXTURE9		texture_;

	D3DXMATRIX world_matrix_;		// スプライトのワールド変換行列
	D3DXMATRIX view_matrix_;		// カメラ変換行列
	D3DXMATRIX projection_matrix_;	// プロジェクション変換行列
};


#endif //SPRITE_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/