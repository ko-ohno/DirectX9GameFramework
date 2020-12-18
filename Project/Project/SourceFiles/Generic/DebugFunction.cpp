/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugSystem.cpp] デバッグシステム
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デバッグシステム
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "DebugFunction.h"

/*-----------------------------------------------------------------------------
/* デバッグ用の文字列データ出力処理
-----------------------------------------------------------------------------*/
std::string DebugFunction::OutputErrorString(std::string inErrorMsg, std::string inFileName, int inLineNumber, std::string inFunctionName)
{
	//ファイル名をだけを取り出す
	std::string file_name = inFileName;
	{
		int str_erase_begin = 0;							//ディレクトリの0文字目
		int str_erase_end = file_name.find_last_of("\\");	//一番最後のディレクトリを検索

		//不要な文字列の削除処理
		file_name.erase(str_erase_begin, str_erase_end + 1);
	}

	//各、文字列の要素をまとめたもの
	std::string file_name_and_line_num  = "ファイル名：" + file_name      + "(" + std::to_string(inLineNumber) + ")\n";
	std::string function_name			= "関数名    ：" + inFunctionName + "()\n";
	std::string error_msg				= "エラー内容：" + inErrorMsg     + "\n";

	return std::string(file_name_and_line_num + function_name + error_msg);
}

void DebugFunction::DebugOutputFormatString(const char* format, ...)
{
#if defined(_DEBUG) || defined(DEBUG)
	va_list valist;
	va_start(valist, format);
	printf(format, valist);
	va_end(valist);
#endif // !_DEBUG
}

/*=============================================================================
/*		End of File
=============================================================================*/