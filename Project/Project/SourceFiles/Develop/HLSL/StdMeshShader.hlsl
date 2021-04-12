/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteShader.hlsl] �X�v���C�g�V�F�[�_�[
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���C�g�V�F�[�_�pHLSL�t�@�C��
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/

struct VS_OUTPUT
{
	float3 pos  : POSITION0;
	float2 texcoord : TEXCOORD0;
	float3 normal   : TEXCOORD1;
};

/*-----------------------------------------------------------------------------
/* �O���[�o���ϐ��錾�u���b�N
-----------------------------------------------------------------------------*/
float4x4	g_MatWorld;					// ���[���h�ϊ��s��
float4x4	g_MatView;					// �r���[�ϊ��s��
float4x4	g_MatProjection;			// �v���W�F�N�V�����ϊ��s��

float4		g_LightDir;					// ���C�g�̌���

float		g_LightStrength;			// ���C�g�̋���

float4		g_Diffuse;					// �g�U���ˌ�
float4		g_Ambient;					// ����
float4		g_Specular;					// ���ʔ��ˌ�
float4		g_Emissive;					// ���Ȕ����F

bool		g_IsDrawTextureColor;		// �e�N�X�`���J���[�̕`������邩�H
bool		g_IsDrawVertexColor;		// ���_�J���[�̕`������邩�H

texture		g_Texture;					//�e�N�X�`�����



/*-----------------------------------------------------------------------------
/* �e�N�X�`���[�T���v���[�u���b�N
-----------------------------------------------------------------------------*/
sampler Sampler = sampler_state {

	texture = <g_Texture>;

	AddressU = WRAP;		// UV�̐ݒ�,�J��Ԃ�
	AddressV = WRAP;		// UV�̐ݒ�,�J��Ԃ�

	MinFilter = LINEAR;		// ���j�A�t�B���^�i�k�����j
	MagFilter = LINEAR;		// ���j�A�t�B���^�i�g�厞�j
	MipFilter = LINEAR;		// ���j�A�t�B���^�i��Ԏ��j

};

/*-----------------------------------------------------------------------------
/* ���_�V�F�[�_�[�v���O�����u���b�N
-----------------------------------------------------------------------------*/
void VS( float3 in_pos	  : POSITION0
	   , float3 in_normal : NORMAL0
	   , float4 in_color  : COLOR0
	   , float2 in_tex	  : TEXCOORD0
	   , out float4 out_pos    : POSITION0
	   , out float4 out_color  : COLOR0
	   , out float2 out_tex    : TEXCOORD0)
{
	// ���W�ϊ�
	out_pos = mul(float4(in_pos, 1.0f), g_MatWorld);
	out_pos = mul(out_pos, g_MatView);				
	out_pos = mul(out_pos, g_MatProjection);

	// �e�N�X�`�����W�����̂܂܏o�͂���
	out_tex = in_tex;

	float3	N;		// ���[���h��ԏ�̖@���x�N�g��
	float3	L;		// ���̍������ޕ���

	// �@�������[���h��ԏ�̃x�N�g���ɕϊ����āA�P�ʃx�N�g����
	N = normalize(mul(in_normal, (float3x3)g_MatWorld));

	//���C�g�̉��̌���
	float3 light_dir = float3(0.0f, -1.0f, 0.0f);

	// ���s���̍������ޕ���	�P�ʃx�N�g����
	L = normalize(-light_dir);

	out_color = max(0.f, dot(L, N)) * in_color;
}

/*-----------------------------------------------------------------------------
/* �s�N�Z���V�F�[�_�[�v���O�����u���b�N
-----------------------------------------------------------------------------*/
void PS( float4	in_color : COLOR0
	   , float2	in_uv	 : TEXCOORD0
	   , out float4 out_color : COLOR0)
{

	//bool�ŕ`��؂�ւ����s��
	if (g_IsDrawTextureColor)
	{
		//�e�N�X�`���̐F��UV���W�̍���
		float4 tex_color = tex2D(Sampler, in_uv);

		// �e�N�X�`���̐F�ƒ��_�̐F���|�����킹��
		out_color = tex_color * in_color;
	}
	else
	{
		out_color = in_color;
	}
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