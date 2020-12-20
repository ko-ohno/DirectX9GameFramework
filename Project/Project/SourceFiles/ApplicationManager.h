/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ApplicationManager.h] �A�v���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�S�̂̏����̊Ǘ��N���X
=============================================================================*/
#ifndef APPLICATION_MANAGER_H_
#define	APPLICATION_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*-------------------------------------
/* �\����
-------------------------------------*/




/*-------------------------------------
/* �A�v���S�̂̏����̊Ǘ��N���X
-------------------------------------*/
class ApplicationManager
{
private:
	ApplicationManager(void);

public:
	~ApplicationManager(void);

	static ApplicationManager* Create(void);

	static bool Init(void);
	static void Uninit(void);
	static void Input(void);
	static void Update(float deltaTime);
	static void GenerateOutput(void);

private:
};

#endif //APPLICATION_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/