void VS(float3 in_pos : POSITION0
	, float2 in_tex : TEXCOORD0
	, out float4 out_pos : POSITION0
	, out float2 out_tex : TEXCOORD0)
{
	// 座標変換
	out_pos = mul(float4(in_pos, 1.0f), g_world_matrix);	// 頂点座標（ローカル座標系）をワールド座標系に変換	
	out_pos = mul(out_pos, g_view_matrix);					// 頂点座標（ワールド座標系）をカメラ座標系に変換
	out_pos = mul(out_pos, g_projectionmatrix);				// 頂点座標（カメラ座標系）をスクリーン座標系に変換
	out_tex = in_tex;
}
