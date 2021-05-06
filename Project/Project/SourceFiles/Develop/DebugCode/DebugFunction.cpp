/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugFunction.cpp] �f�o�b�O�֐�
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f�o�b�O�֐�
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "DebugFunction.h"

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* �f�o�b�O�p�̕�����f�[�^�o�͏���
-----------------------------------------------------------------------------*/
std::string DebugFunction::OutputFormatString(const std::string& fileName, int lineNumber, const std::string& functionName, const char* format, ...)
{
	//�t�@�C���������������o��
	std::string file_name     = fileName;
	{
		int str_erase_begin = 0;							//�f�B���N�g����0������
		int str_erase_end = file_name.find_last_of("\\");	//��ԍŌ�̃f�B���N�g��������

		//�s�v�ȕ�����̍폜����
		file_name.erase(str_erase_begin, str_erase_end + 1);
	}

	//�t�H�[�}�b�g�t��������̏���
	std::string format_str;
	{
		char buf[1024];
		va_list valist;
		va_start(valist, format);
		vsprintf(buf, format, valist);
		format_str = Format(buf, valist);
		va_end(valist);
	}

	//�e�A������̗v�f���܂Ƃ߂�����
	std::string file_name_and_line_num  = "�t�@�C�����F" + file_name	 + "(" + std::to_string(lineNumber) + ")\n";
	std::string function_name			= "�֐���    �F" + functionName  + "()\n";
	std::string error_msg				= "�G���[���e�F" + format_str	 + "\n";

	return std::string(file_name_and_line_num + function_name + error_msg);
}

/*-----------------------------------------------------------------------------
/*�@�x�����b�Z�[�W�{�b�N�X�ɑ΂���printf
-----------------------------------------------------------------------------*/
void DebugFunction::PrintfToWarningMessageBox(const char* format, ...)
{
	char buf[1024];
	va_list valist;
	va_start(valist, format);
	vsprintf(buf, format, valist);
	MessageBox(nullptr, buf, "Warning !!", (MB_OK | MB_ICONWARNING));
	va_end(valist);
}

/*-----------------------------------------------------------------------------
/*�@�G���[���b�Z�[�W�{�b�N�X�ɑ΂���printf
-----------------------------------------------------------------------------*/
void DebugFunction::PrintfToErrorMessageBox(const char* format, ...)
{
	char buf[1024];
	va_list valist;
	va_start(valist, format);
	vsprintf(buf, format, valist);
	MessageBox(nullptr, buf, "Error !!", (MB_OK | MB_ICONERROR));
	va_end(valist);
	abort();
}

/*-----------------------------------------------------------------------------
/* VisualStudio�������^�C�����̏o�̓E�B���h�E�ɑ΂���printf
-----------------------------------------------------------------------------*/
void DebugFunction::PrintfToIDERuntimeOutputWindow(const char* format, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	char buf[1024];
	va_list valist;
	va_start(valist, format);
	vsprintf(buf, format, valist);
	OutputDebugString(buf);
	va_end(valist);
#endif // !_DEBUG
}

/*-----------------------------------------------------------------------------
/* �R���\�[�����[�U�C���^�[�t�F�[�X�ɑ΂���printf
-----------------------------------------------------------------------------*/
void DebugFunction::PrintfToCUIWindow(const char* format, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif // !_DEBUG
}

/*=============================================================================
/*		End of File
=============================================================================*/