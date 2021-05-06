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
	float4 pos		: POSITION0;
	float4 color    : COLOR0;
	float2 texcoord : TEXCOORD0;
};

/*-----------------------------------------------------------------------------
/* グローバル変数宣言ブロック
-----------------------------------------------------------------------------*/
float4x4	g_MatWorld;					// ワールド変換行列
float4x4	g_MatView;					// ビュー変換行列
float4x4	g_MatProjection;			// プロジェクション変換行列

float4		g_LightDir;					// ライトの向き

float		g_LightPower;				// ライトの強さ

float4		g_Diffuse;					// 拡散反射光
float4		g_Ambient;					// 環境光
float4		g_Specular;					// 鏡面反射光
float4		g_Emissive;					// 自己発光色

bool		g_IsDrawTextureColor;		// テクスチャカラーの描画をするか？

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
VS_OUTPUT VS( float4 in_pos	   : POSITION0
			, float4 in_normal : NORMAL0
			, float4 in_color  : COLOR0
			, float2 in_tex	   : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = float4(1.0f, 1.0f, 1.0f, 1.0f);

	// 座標変換
	pos = mul(in_pos, g_MatWorld);
	pos = mul(pos, g_MatView);
	pos = mul(pos, g_MatProjection);

	// 頂点座標をそのまま　　
	Out.pos = pos;

	// ライティングの計算
	{
		float4 dir = -normalize(g_LightDir);

		if (g_IsDrawTextureColor)
		{
			//法線を単位ベクトル化
			float4 out_color = g_Diffuse * max(dot(dir, in_normal), (float4)0.f) + g_Ambient;
			float power = g_LightPower;
			
			//ハーフランバートシェーダの計算式
			power = power * 0.5f + 0.5f;
			power = power * power;

			Out.color = out_color * power;
		}
		else
		{
			//そのまま表示
			Out.color = in_color;
		}
	}

	//UV座標をそのまま出力
	Out.texcoord = in_tex;

	return Out;
}

/*-----------------------------------------------------------------------------
/* ピクセルシェーダープログラムブロック
-----------------------------------------------------------------------------*/
float4 PS(VS_OUTPUT In) : COLOR0
{
	if (g_IsDrawTextureColor)
	{
		return In.color * tex2D(Sampler, In.texcoord);
	}
	else
	{
		return In.color;
	}
}


// プリミティブ用のメッシュの頂点シェーダー

VS_OUTPUT PrimitiveMeshVS( float4 in_pos	: POSITION0
						 , float4 in_normal : NORMAL0
						 , float4 in_color  : COLOR0
						 , float2 in_tex    : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = float4(1.0f, 1.0f, 1.0f, 1.0f);

	// 座標変換
	pos = mul(in_pos, g_MatWorld);
	pos = mul(pos, g_MatView);
	pos = mul(pos, g_MatProjection);

	// 頂点座標をそのまま　　
	Out.pos = pos;

	// ライティングの計算
	{
		float4 dir = -normalize(g_LightDir);		

		//法線を単位ベクトル化
		Out.color = g_Diffuse * max(dot(dir, in_normal), (float4)0.f) + g_Ambient;
	
	}

	//UV座標をそのまま出力
	Out.texcoord = in_tex;

	return Out;
}


// プリミティブ用のメッシュのピクセルシェーダー

float4 PrimitiveMeshPS(VS_OUTPUT In) : COLOR0
{
	return In.color;
}

/*-----------------------------------------------------------------------------
/* テクニック宣言ブロック
-----------------------------------------------------------------------------*/
technique Tech {
	pass p0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();

		ZEnable = true;
		ZWriteEnable = true;
	}
}

// プリミティブメッシュ用のテクニック
technique Tech2 {
	pass p0 {
		VertexShader = compile vs_3_0 PrimitiveMeshVS();
		PixelShader = compile ps_3_0 PrimitiveMeshPS();

		ZEnable = true;
		ZWriteEnable = true;
		//FillMode = WIREFRAME;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/