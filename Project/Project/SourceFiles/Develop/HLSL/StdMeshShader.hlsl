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
	float4 pos		: POSITION0;
	float4 color    : COLOR0;
	float2 texcoord : TEXCOORD0;
};

/*-----------------------------------------------------------------------------
/* �O���[�o���ϐ��錾�u���b�N
-----------------------------------------------------------------------------*/
float4x4	g_MatWorld;					// ���[���h�ϊ��s��
float4x4	g_MatView;					// �r���[�ϊ��s��
float4x4	g_MatProjection;			// �v���W�F�N�V�����ϊ��s��

float4		g_LightDir;					// ���C�g�̌���

float		g_LightPower;				// ���C�g�̋���

float4		g_Diffuse;					// �g�U���ˌ�
float4		g_Ambient;					// ����
float4		g_Specular;					// ���ʔ��ˌ�
float4		g_Emissive;					// ���Ȕ����F

bool		g_IsDrawTextureColor;		// �e�N�X�`���J���[�̕`������邩�H

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
VS_OUTPUT VS( float4 in_pos	   : POSITION0
			, float4 in_normal : NORMAL0
			, float4 in_color  : COLOR0
			, float2 in_tex	   : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = float4(1.0f, 1.0f, 1.0f, 1.0f);

	// ���W�ϊ�
	pos = mul(in_pos, g_MatWorld);
	pos = mul(pos, g_MatView);
	pos = mul(pos, g_MatProjection);

	// ���_���W�����̂܂܁@�@
	Out.pos = pos;

	// ���C�e�B���O�̌v�Z
	{
		float4 dir = -normalize(g_LightDir);

		if (g_IsDrawTextureColor)
		{
			//�@����P�ʃx�N�g����
			float4 out_color = g_Diffuse * max(dot(dir, in_normal), (float4)0.f) + g_Ambient;
			float power = g_LightPower;
			
			//�n�[�t�����o�[�g�V�F�[�_�̌v�Z��
			power = power * 0.5f + 0.5f;
			power = power * power;

			Out.color = out_color * power;
		}
		else
		{
			//���̂܂ܕ\��
			Out.color = in_color;
		}
	}

	//UV���W�����̂܂܏o��
	Out.texcoord = in_tex;

	return Out;
}

/*-----------------------------------------------------------------------------
/* �s�N�Z���V�F�[�_�[�v���O�����u���b�N
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


// �v���~�e�B�u�p�̃��b�V���̒��_�V�F�[�_�[

VS_OUTPUT PrimitiveMeshVS( float4 in_pos	: POSITION0
						 , float4 in_normal : NORMAL0
						 , float4 in_color  : COLOR0
						 , float2 in_tex    : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = float4(1.0f, 1.0f, 1.0f, 1.0f);

	// ���W�ϊ�
	pos = mul(in_pos, g_MatWorld);
	pos = mul(pos, g_MatView);
	pos = mul(pos, g_MatProjection);

	// ���_���W�����̂܂܁@�@
	Out.pos = pos;

	// ���C�e�B���O�̌v�Z
	{
		float4 dir = -normalize(g_LightDir);		

		//�@����P�ʃx�N�g����
		Out.color = g_Diffuse * max(dot(dir, in_normal), (float4)0.f) + g_Ambient;
	
	}

	//UV���W�����̂܂܏o��
	Out.texcoord = in_tex;

	return Out;
}


// �v���~�e�B�u�p�̃��b�V���̃s�N�Z���V�F�[�_�[

float4 PrimitiveMeshPS(VS_OUTPUT In) : COLOR0
{
	return In.color;
}

/*-----------------------------------------------------------------------------
/* �e�N�j�b�N�錾�u���b�N
-----------------------------------------------------------------------------*/
technique Tech {
	pass p0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();

		ZEnable = true;
		ZWriteEnable = true;
	}
}

// �v���~�e�B�u���b�V���p�̃e�N�j�b�N
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