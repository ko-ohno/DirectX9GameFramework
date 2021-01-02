void VS(float3 in_pos : POSITION0
	, float2 in_tex : TEXCOORD0
	, out float4 out_pos : POSITION0
	, out float2 out_tex : TEXCOORD0)
{
	// ���W�ϊ�
	out_pos = mul(float4(in_pos, 1.0f), g_world_matrix);	// ���_���W�i���[�J�����W�n�j�����[���h���W�n�ɕϊ�	
	out_pos = mul(out_pos, g_view_matrix);					// ���_���W�i���[���h���W�n�j���J�������W�n�ɕϊ�
	out_pos = mul(out_pos, g_projectionmatrix);				// ���_���W�i�J�������W�n�j���X�N���[�����W�n�ɕϊ�
	out_tex = in_tex;
}
