/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[MainProcess.h] ���C���̎��s����
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���C���̎��s����
=============================================================================*/
#ifndef MAIN_PROCESS_H_
#define	MAIN_PROCESS_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* ���C���̎��s�����N���X
-------------------------------------*/
class MainProcess
{
public:
	MainProcess(void);
	~MainProcess(void);

public:
	bool StartUp(void);
	void Run(void);
	void ShutDown(void);

private:
	bool Init(void);
	void Uninit(void);
	void Input(void);
	void Update(float deltaTime);
	void GenerateOutput(void);

private:
	class Manager* manager_;
};


#endif //MAIN_PROCESS_H_
/*=============================================================================
/*		End of File
=============================================================================*/