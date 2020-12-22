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

 /*! @brief  OUTPUT_ERROR_MSG()��,�f�o�b�O�p�̃G���[���b�Z�[�W������𐶐����܂��B
 //  @param [in]�p�����[�^�ɂ́Achar*�^�z�񂩁Astd::string�^��n���Ă��������B
 //  @return OUTPUT_ERROR_MSG()�́A���̃}�N���̌Ăяo�����"�\�[�X�t�@�C����" �� "�s�ԍ�" �� "�֐���" ����сA
 // ���̃}�N����"�����ɒ�`�����G���[���e�̕�����" ���܂� std::string�^�̕�����f�[�^���o�͂��܂��B
 */
#define OUTPUT_ERROR_MSG(errorMsg) \
(\
	DebugFunction::OutputErrorString(errorMsg, __FILE__, __LINE__, __FUNCTION__) \
);
//#define OUTPUT_ERROR_MSG(errorMsg, ...) (DebugFunction::OutputErrorString(errorMsg, __FILE__, __LINE__, __FUNCTION__));

/*-------------------------------------
/* �f�o�b�O�֐�
-------------------------------------*/
namespace DebugFunction
{
	// @brief OutputErrorString()�́A�f�o�b�O�p�̃G���[���b�Z�[�W������𐶐����܂��B
	// @param [in] �G���[���e�ƂȂ� "������f�[�^" ����́B
	// @param [in] ���̊֐��̌Ăяo����� "�t�@�C����" ����́B
	// @param [in] ���̊֐��̌Ăяo����� "�s�ԍ�" ����́B
	// @param [in] ���̊֐����Ăяo����� "�֐���" �����
	// @return ���ׂẴp�����[�^�����������A�f�o�b�O�p�̃G���[���b�Z�[�W������𐶐����܂��B
	std::string OutputErrorString(std::string inErrorMsg
						         , std::string inFileName
						         , int inLineNumber
						         , std::string inFunctionName);

	// @brief VisualStudio�̏o�̓E�B���h�E�Ƀt�H�[�}�b�g�t���������\��
	// @param format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param �ϒ��ϐ�
	// @remarks ���̊֐��̓f�o�b�O�p�ł��A�f�o�b�O���ɂ������삵�܂���
	void OutputDebugFormatString(const char* format, ...);


	// @brief �R���\�[����ʂɃt�H�[�}�b�g�t���������\��
	// @param format �t�H�[�}�b�g  (%d�Ƃ�%f�Ƃ���)
	// @param �ϒ��ϐ�
	// @remarks ���̊֐��̓f�o�b�O�p�ł��A�f�o�b�O���ɂ������삵�܂���
	void OutputDebugConsoleFormatString(const char* format, ...);

};


#endif //DEBUG_FUNCTION_H_
/*=============================================================================
/*		End of File
=============================================================================*/
