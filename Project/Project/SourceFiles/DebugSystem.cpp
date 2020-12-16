/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugSystem.cpp] �f�o�b�O�V�X�e��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f�o�b�O�V�X�e��
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "StdAfx.h"
#include "DebugSystem.h"

/*-----------------------------------------------------------------------------
/* �f�o�b�O�p�̕�����f�[�^�o�͏���
-----------------------------------------------------------------------------*/
std::string DebugSystem::OutputErrorString(std::string inErrorMsg, std::string inFileName, int inLineNumber, std::string inFunctionName)
{
	//�t�@�C���������������o��
	std::string file_name = inFileName;
	{
		int str_erase_begin = 0;							//�f�B���N�g����0������
		int str_erase_end = file_name.find_last_of("\\");	//��ԍŌ�̃f�B���N�g��������

		//�s�v�ȕ�����̍폜����
		file_name.erase(str_erase_begin, str_erase_end + 1);
	}

	//�e�A������̗v�f���܂Ƃ߂�����
	std::string file_name_and_line_num  = "�t�@�C�����F" + file_name      + "(" + std::to_string(inLineNumber) + ")\n";
	std::string function_name			= "�֐���    �F" + inFunctionName + "()\n";
	std::string error_msg				= "�G���[���e�F" + inErrorMsg     + "\n";

	return std::string(file_name_and_line_num + function_name + error_msg);
}

/*=============================================================================
/*		End of File
=============================================================================*/