/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONManager.h] JSON管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：JSON管理クラス
=============================================================================*/
#ifndef JSON_MANAGER_H_
#define	JSON_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------	   
/* JSON管理クラス
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

	//ロードとセーブ関係
	static bool LoadJSON(const std::string& inFileName, rapidjson::Document& outDoc);

private:
	//解析エラーのメッセージ
	static const char* GetParseErrorMsg(rapidjson::ParseErrorCode inParseErrorCode, const LanguageSetting inSelectLanguage);
	static const char* GetParseError_Jp(rapidjson::ParseErrorCode inParseErrorCode);
};

#endif //JSON_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/