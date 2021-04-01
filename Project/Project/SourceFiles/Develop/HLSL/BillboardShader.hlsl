/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardShader.hlsl] ビルボードシェーダ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ビルボードシェーダ用HLSLファイル
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
float4x4	g_MatTranslation;
float4x4	g_MatScale;
float4x4	g_MatInverseView;
float4x4	g_MatView;
float4x4	g_MatProjection;

texture		g_Texture;

float4x4 g_Identity =
{
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 1 }
};

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
void VS(float3 in_pos : POSITION0
	   , float4 in_color : COLOR0
	   , float2 in_tex : TEXCOORD0
	   , out float4 out_pos : POSITION0
	   , out float4 out_color : COLOR0
	   , out float2 out_tex : TEXCOORD0)
{
	float4x4 world_matrix = g_Identity;
	world_matrix = mul(world_matrix, g_MatInverseView);
	world_matrix = mul(world_matrix, g_MatScale);
	world_matrix = mul(world_matrix, g_MatTranslation);

	out_pos = mul(float4(in_pos, 1.0f), world_matrix);	// ワールド座標
	out_pos = mul(out_pos, g_MatView);					// ビュー座標
	out_pos = mul(out_pos, g_MatProjection);			// 頂点座標（カメラ座標系）をスクリーン座標系に変換
	out_color = in_color;
	out_tex = in_tex;
}

/*-----------------------------------------------------------------------------
/* ピクセルシェーダープログラムブロック
-----------------------------------------------------------------------------*/
void PS(float4	in_color : COLOR0
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
		PixelShader = compile ps_3_0 PS();

		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/