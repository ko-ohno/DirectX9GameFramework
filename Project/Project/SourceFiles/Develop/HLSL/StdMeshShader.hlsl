/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.hlsl] �X�v���C�g�V�F�[�_�[
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�V�F�[�_�pHLSL�t�@�C��
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/

struct VS_INPUT
{
	float3 vtx_pos : POSITION0;
	float4 vtx_col : COLOR0;
	float2 vtx_uv  : TEXCOORD0;
};

/*-----------------------------------------------------------------------------
/* �O���[�o���ϐ��錾�u���b�N
-----------------------------------------------------------------------------*/
float4x4	g_MatWorld;				// ���[���h�ϊ��s��
float4x4	g_MatView;				// �r���[�ϊ��s��
float4x4	g_MatProjection;		// �v���W�F�N�V�����ϊ��s��

float4		g_LightDir;				// ���C�g�̌���

float		g_LightStrength;		// ���C�g�̋���

float4		g_Diffuse;				// �g�U���ˌ�
float4		g_Ambient;				// ����
float4		g_Specular;				// ���ʔ��ˌ�
float4		g_Emissive;				// ���Ȕ����F

texture		g_Texture;


/*-----------------------------------------------------------------------------
/* �e�N�X�`���[�T���v���[�u���b�N
-----------------------------------------------------------------------------*/
sampler Sampler = sampler_state {

	texture = <g_Texture>;

	AddressU = WRAP;		// UV�̐ݒ�,�J��Ԃ�
	AddressV = WRAP;		// UV�̐ݒ�,�J��Ԃ�

	MinFilter = LINEAR;		// ���j�A�t�B���^�i�k�����j
	MagFilter = LINEAR;		// ���j�A�t�B���^�i�g�厞�j
	MipFilter = LINEAR;

};

/*-----------------------------------------------------------------------------
/* ���_�V�F�[�_�[�v���O�����u���b�N
-----------------------------------------------------------------------------*/
void VS(float3 in_pos : POSITION0
	, float4 in_color : COLOR0
	, float2 in_tex : TEXCOORD0
	, out float4 out_pos : POSITION0
	, out float4 out_color : COLOR0
	, out float2 out_tex : TEXCOORD0)
{
	// ���W�ϊ�
	out_pos = mul(float4(in_pos, 1.0f), g_MatWorld);	// ���_���W�i�J�������W�n�j���X�N���[�����W�n�ɕϊ�
	out_pos = mul(out_pos, g_MatView);					// ���_���W�i�J�������W�n�j���X�N���[�����W�n�ɕϊ�
	out_pos = mul(out_pos, g_MatProjection);			// ���_���W�i�J�������W�n�j���X�N���[�����W�n�ɕϊ�
	out_color = in_color;
	out_tex = in_tex;
}

/*-----------------------------------------------------------------------------
/* �s�N�Z���V�F�[�_�[�v���O�����u���b�N
-----------------------------------------------------------------------------*/
void PS(float4	in_color : COLOR0
	, float2	in_uv : TEXCOORD0
	, out float4 out_color : COLOR0)
{
	//�e�N�X�`���̐F��UV���W�̍���
	float4 texcol = tex2D(Sampler, in_uv) * in_color;	// R G B A

	//���ׂĂ̗v�f�����������e�N�X�`�����J���[�Ƃ��ďo��
	//out_color = texcol;

	out_color = float4(0.5f, 1.0f, 0.5f, 1.0f);
}

/*-----------------------------------------------------------------------------
/* �e�N�j�b�N�錾�u���b�N
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