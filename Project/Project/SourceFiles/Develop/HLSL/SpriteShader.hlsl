/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.hlsl] スプライトシェーダー
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダ用HLSLファイル
=============================================================================*/

/*--- インクルードファイル ---*/

struct VS_INPUT
{
	float3 vtx_pos : POSITION0;
	float4 vtx_col : COLOR0;
	float2 vtx_uv  : TEXCOORD0;
};

/*-----------------------------------------------------------------------------
/* グローバル変数宣言ブロック
-----------------------------------------------------------------------------*/
float4x4	g_MatProjection;			// プロジェクション変換行列
texture		g_Texture;

/*-----------------------------------------------------------------------------
/* テクスチャーサンプラーブロック
-----------------------------------------------------------------------------*/
sampler Sampler = sampler_state {

	texture = <g_Texture>;

	AddressU = WRAP;		// UVの設定,繰り返し
	AddressV = WRAP;		// UVの設定,繰り返し

	MinFilter = LINEAR;		// リニアフィルタ（縮小時）
	MagFilter = LINEAR;		// リニアフィルタ（拡大時）
	MipFilter = LINEAR;

};

/*-----------------------------------------------------------------------------
/* 頂点シェーダープログラムブロック
-----------------------------------------------------------------------------*/
void VS( float3 in_pos : POSITION0
	   , float4 in_color : COLOR0 
       , float2 in_tex : TEXCOORD0
	   , out float4 out_pos : POSITION0
	   , out float4 out_color : COLOR0
	   , out float2 out_tex : TEXCOORD0)
{
	// 座標変換
	out_pos		= float4(in_pos, 1.0f);
	out_pos		= mul(out_pos, g_MatProjection);			// 頂点座標（カメラ座標系）をスクリーン座標系に変換
	out_color	= in_color;
	out_tex		= in_tex;
}

/*-----------------------------------------------------------------------------
/* ピクセルシェーダープログラムブロック
-----------------------------------------------------------------------------*/
void PS( float4	in_color : COLOR0
	   , float2	in_uv : TEXCOORD0
	   , out float4 out_color : COLOR0)
{
	//テクスチャの色とUV座標の合成
	float4 texcol = tex2D(Sampler, in_uv) * in_color;	// R G B A
	
	//すべての要素を合成したテクスチャをカラーとして出力
	out_color = texcol;
}

/*-----------------------------------------------------------------------------
/* テクニック宣言ブロック
-----------------------------------------------------------------------------*/
technique Tech {
	pass p0 {

		VertexShader = compile vs_3_0 VS();
		PixelShader  = compile ps_3_0 PS();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/