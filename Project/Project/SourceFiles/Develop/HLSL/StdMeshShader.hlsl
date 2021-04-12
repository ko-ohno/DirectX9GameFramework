/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.hlsl] スプライトシェーダー
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダ用HLSLファイル
=============================================================================*/

/*--- インクルードファイル ---*/

struct VS_OUTPUT
{
	float3 pos  : POSITION0;
	float2 texcoord : TEXCOORD0;
	float3 normal   : TEXCOORD1;
};

/*-----------------------------------------------------------------------------
/* グローバル変数宣言ブロック
-----------------------------------------------------------------------------*/
float4x4	g_MatWorld;					// ワールド変換行列
float4x4	g_MatView;					// ビュー変換行列
float4x4	g_MatProjection;			// プロジェクション変換行列

float4		g_LightDir;					// ライトの向き

float		g_LightStrength;			// ライトの強さ

float4		g_Diffuse;					// 拡散反射光
float4		g_Ambient;					// 環境光
float4		g_Specular;					// 鏡面反射光
float4		g_Emissive;					// 自己発光色

bool		g_IsDrawTextureColor;		// テクスチャカラーの描画をするか？
bool		g_IsDrawVertexColor;		// 頂点カラーの描画をするか？

texture		g_Texture;					//テクスチャ情報



/*-----------------------------------------------------------------------------
/* テクスチャーサンプラーブロック
-----------------------------------------------------------------------------*/
sampler Sampler = sampler_state {

	texture = <g_Texture>;

	AddressU = WRAP;		// UVの設定,繰り返し
	AddressV = WRAP;		// UVの設定,繰り返し

	MinFilter = LINEAR;		// リニアフィルタ（縮小時）
	MagFilter = LINEAR;		// リニアフィルタ（拡大時）
	MipFilter = LINEAR;		// リニアフィルタ（補間時）

};

/*-----------------------------------------------------------------------------
/* 頂点シェーダープログラムブロック
-----------------------------------------------------------------------------*/
void VS( float3 in_pos	  : POSITION0
	   , float3 in_normal : NORMAL0
	   , float4 in_color  : COLOR0
	   , float2 in_tex	  : TEXCOORD0
	   , out float4 out_pos    : POSITION0
	   , out float4 out_color  : COLOR0
	   , out float2 out_tex    : TEXCOORD0)
{
	// 座標変換
	out_pos = mul(float4(in_pos, 1.0f), g_MatWorld);
	out_pos = mul(out_pos, g_MatView);				
	out_pos = mul(out_pos, g_MatProjection);

	// テクスチャ座標をそのまま出力する
	out_tex = in_tex;

	float3	N;		// ワールド空間上の法線ベクトル
	float3	L;		// 光の差し込む方向

	// 法線をワールド空間上のベクトルに変換して、単位ベクトル化
	N = normalize(mul(in_normal, (float3x3)g_MatWorld));

	//ライトの仮の向き
	float3 light_dir = float3(0.0f, -1.0f, 0.0f);

	// 平行光の差し込む方向	単位ベクトル化
	L = normalize(-light_dir);

	out_color = max(0.f, dot(L, N)) * in_color;
}

/*-----------------------------------------------------------------------------
/* ピクセルシェーダープログラムブロック
-----------------------------------------------------------------------------*/
void PS( float4	in_color : COLOR0
	   , float2	in_uv	 : TEXCOORD0
	   , out float4 out_color : COLOR0)
{

	//boolで描画切り替えを行う
	if (g_IsDrawTextureColor)
	{
		//テクスチャの色とUV座標の合成
		float4 tex_color = tex2D(Sampler, in_uv);

		// テクスチャの色と頂点の色を掛け合わせる
		out_color = tex_color * in_color;
	}
	else
	{
		out_color = in_color;
	}
}

/*-----------------------------------------------------------------------------
/* テクニック宣言ブロック
-----------------------------------------------------------------------------*/
technique Tech {
	pass p0 {

		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();

		AlphaBlendEnable = true;
		SrcBlend  = SRCALPHA;
		DestBlend = INVSRCALPHA;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/