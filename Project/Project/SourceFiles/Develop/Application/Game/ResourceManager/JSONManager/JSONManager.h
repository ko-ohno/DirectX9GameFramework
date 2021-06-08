/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONManager.h] JSON�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FJSON�Ǘ��N���X
=============================================================================*/
#ifndef JSON_MANAGER_H_
#define	JSON_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------	   
/* JSON�Ǘ��N���X
-------------------------------------*/
class JSONManager
{
private:
	enum class LanguageSetting
	{
		None = -1
		, Jp
		, En
		, Max
	};

private:
	JSONManager(void);

public:
	~JSONManager(void);

	//���[�h�ƃZ�[�u�֌W
	static bool LoadJSON(const std::string& inFileName, rapidjson::Document& outDoc);

private:
	//��̓G���[�̃��b�Z�[�W
	static const char* GetParseErrorMsg(rapidjson::ParseErrorCode inParseErrorCode, const LanguageSetting inSelectLanguage);
	static const char* GetParseError_Jp(rapidjson::ParseErrorCode inParseErrorCode);
};

#endif //JSON_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/