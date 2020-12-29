/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugFunction.h] �f�o�b�O�֐�
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f�o�b�O�֐�
=============================================================================*/
#ifndef DEBUG_FUNCTION_H_
#define	DEBUG_FUNCTION_H_


/*--- �C���N���[�h�t�@�C�� ---*/

/*-------------------------------------
/* �\����
-------------------------------------*/


/*--- �}�N����` ---*/

// �g�ݍ��݃}�N���̓W�J��𐧌䂷�邽�߂ɁA�����񑀍�����邽�߂̊֐����A�}�N����`�ɓ�������B

 /*! @brief ���̃}�N���́A�u�Ăяo����́v"�t�@�C����"��"�s�ԍ�"�A"�֐���"����肵�A�������Ɏw�肵���t�H�[�}�b�g�t��������𐶐����܂�
//  @param [in] format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
//  @param [in] ���̃p�����[�^�ɂ́Achar*�^���Astd::string�^�Ȃǂ̕������n���Ă��������B
//  @return ���̃}�N���̌Ăяo�����"�\�[�X�t�@�C����" �� "�s�ԍ�" �� "�֐���" ����сA"�������Ɏw�肵���t�H�[�}�b�g�t��������" �𕡍�����std::string�^�̕�����f�[�^���o�͂��܂��B
*/
#define OUTPUT_FORMAT_STRING(format, ...) ( DebugFunction::OutputFormatString(__FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__) )

/*-------------------------------------
/* �f�o�b�O�֐�
-------------------------------------*/
namespace DebugFunction
{
	//std::string�^�Ńt�H�[�}�b�g�t����������������߂̃e���v���[�g�֐�
	template <typename ... Args>
	std::string Format(const std::string& fmt, Args ... args)
	{
		size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
		std::vector<char> buf(len + 1);
		std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
		return std::string(&buf[0], &buf[0] + len);
	}

	// @brief �f�o�b�O�p�̃G���[���b�Z�[�W�p�̃t�H�[�}�b�g�t�������񐶐����܂��B
	// @param [in] format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param [in] ���̊֐��̌Ăяo����� "�t�@�C����" ����́B
	// @param [in] ���̊֐��̌Ăяo����� "�s�ԍ�" ����́B
	// @param [in] ���̊֐����Ăяo����� "�֐���" �����
	// @return ���ׂẴp�����[�^�����������A�f�o�b�O�p�̃G���[���b�Z�[�W������𐶐����܂��B
	std::string OutputFormatString(const std::string& fileName, int lineNumber, const std::string& functionName, const char* format, ...);

	// @brief ���[�j���O�����ɑ΂��Ă͂��̊֐����g���B���b�Z�[�W�{�b�N�X�Ƀt�H�[�}�b�g�t���������\��
	// @param [in] format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param [in] �ϒ��ϐ�
	// @remarks ���̊֐��̓p�����[�^�Ɏw�肳�ꂽ�x�����b�Z�[�W��\�����܂��B
	void PrintfToWarningMessageBox(const char* format, ...);

	// @brief �G���[�����ɑ΂��Ă͂��̊֐����g���Bassert()�Ƀt�H�[�}�b�g�t���������\��
	// @param [in] format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param [in] �ϒ��ϐ�
	// @remarks ���̊֐��̓p�����[�^�Ɏw�肳�ꂽ�G���[���b�Z�[�W��\�����܂��B
	void PrintfToErrorMessageBox(const char* format, ...);

	// @brief VisualStudio�������^�C�����̏o�̓E�B���h�E�Ƀt�H�[�}�b�g�t���������\��
	// @param [in] format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param [in] �ϒ��ϐ�
	// @remarks ���̊֐��̓f�o�b�O�p�ł��A�f�o�b�O���ɂ������삵�܂���
	void PrintfToIDERuntimeOutputWindow(const char* format, ...);


	// @brief �R�}���h���C�� �C���^�[�t�F�[�X �Ƀt�H�[�}�b�g�t���������\��
	// @param [in] format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param [in] �ϒ��ϐ�
	// @remarks ���̊֐��̓f�o�b�O�p�ł��A�f�o�b�O���ɂ������삵�܂���
	void PrintfToCUIWindow(const char* format, ...);

};


#endif //DEBUG_FUNCTION_H_
/*=============================================================================
/*		End of File
=============================================================================*/
