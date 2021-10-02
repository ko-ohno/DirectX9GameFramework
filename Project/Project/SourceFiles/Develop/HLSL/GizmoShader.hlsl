/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GizmoShader.hlsl] ギズモシェーダー
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ギズモシェーダー用HLSLファイル
=============================================================================*/

/*--- インクルードファイル ---*/

struct VS_OUTPUT
{
	float4 pos		: SV_POSITION0;
	float4 color    : COLOR0;
};

/*-----------------------------------------------------------------------------
/* グローバル変数宣言ブロック
-----------------------------------------------------------------------------*/
float4x4	g_MatWorld;					// ワールド変換行列
float4x4	g_MatView;					// ビュー変換行列
float4x4	g_MatProjection;			// プロジェクション変換行列

float4		g_Color;					// ギズモの色

/*-----------------------------------------------------------------------------
/* テクスチャーサンプラーブロック
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
/* 頂点シェーダープログラムブロック
-----------------------------------------------------------------------------*/
VS_OUTPUT VS(float4 in_pos		: POSITION0
			, float4 in_color	: COLOR0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = float4(1.0f, 1.0f, 1.0f, 1.0f);

	// 座標変換
	pos = mul(in_pos, g_MatWorld);
	pos = mul(pos, g_MatView);
	pos = mul(pos, g_MatProjection);

	// 頂点座標をそのまま　　
	Out.pos = pos;

	//設定した色にする
	Out.color = g_Color;

	return Out;
}

/*-----------------------------------------------------------------------------
/* ピクセルシェーダープログラムブロック
-----------------------------------------------------------------------------*/
float4 PS(VS_OUTPUT In) : COLOR0
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
		FillMode = WIREFRAME;
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/