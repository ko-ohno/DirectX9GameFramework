/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.hlsl] スプライトシェーダー
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダ用HLSLファイル
=============================================================================*/

/*--- インクルードファイル ---*/


/*-----------------------------------------------------------------------------
/* グローバル変数宣言ブロック
-----------------------------------------------------------------------------*/
float4x4 	g_MatWorld;					// ワールド行列
float4x4	g_MatView;					// カメラ変換行列
float4x4	g_MatProjection;			// プロジェクション変換行列
float4		g_Color;
texture		g_Texture;

/*-----------------------------------------------------------------------------
/* テクスチャーサンプラーブロック
-----------------------------------------------------------------------------*/
sampler Sampler = sampler_state {
	texture = <g_Texture>;

	MinFilter = LINEAR;		// リニアフィルタ（縮小時）
	MagFilter = LINEAR;		// リニアフィルタ（拡大時）

	AddressU = WRAP;		// UVの設定,繰り返し
	AddressV = WRAP;		// UVの設定,繰り返し
};

/*-----------------------------------------------------------------------------
/* 頂点シェーダープログラムブロック
-----------------------------------------------------------------------------*/
void VS( float3 in_pos : POSITION0
       , float2 in_tex : TEXCOORD0
	   , out float4 out_pos : POSITION0
	   , out float2 out_tex : TEXCOORD0)
{
	// 座標変換
	out_pos = mul(float4(in_pos, 1.0f), g_MatProjection);	// 頂点座標（ローカル座標系）をワールド座標系に変換	
	//out_pos = mul(out_pos, g_MatView);					// 頂点座標（ワールド座標系）をカメラ座標系に変換
	//out_pos = mul(out_pos, g_MatProjection);			// 頂点座標（カメラ座標系）をスクリーン座標系に変換
	out_tex = in_tex;
}

/*-----------------------------------------------------------------------------
/* ピクセルシェーダープログラムブロック
-----------------------------------------------------------------------------*/
void PS( float4	in_color  : COLOR0
	   , float2	in_tex    : TEXCOORD0
	   , out float4 out_color : COLOR0)
{
   // 固定の色で出力
  // out_color = float4(0.0f, 1.0f, 0.0, 1.0);			// R G B A
   float4 texcol = tex2D(Sampler, in_tex);
   //texcol.x = 0.f;
   //texcol.y = 0.f;
   //texcol.z = 0.f;
   //texcol.w = 0.35f;
   //out_color = g_Color;		//RGBA
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