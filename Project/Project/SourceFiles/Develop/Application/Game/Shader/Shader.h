/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Shader.h] �V�F�[�_�[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�V�F�[�_�[�N���X
=============================================================================*/
#ifndef SHADER_H_
#define	SHADER_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �V�F�[�_�[�N���X
-------------------------------------*/
class Shader
{
public:
	Shader(void);
	virtual ~Shader(void);

	static Shader* Create(void);

	void Begin(int num);
	void End(void);


private:

};


#endif //RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/