/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugFunction.cpp] デバッグ関数
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デバッグ関数
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "DebugFunction.h"

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* デバッグ用の文字列データ出力処理
-----------------------------------------------------------------------------*/
std::string DebugFunction::OutputFormatString(const std::string& fileName, int lineNumber, const std::string& functionName, const char* format, ...)
{
	//ファイル名をだけを取り出す
	std::string file_name     = fileName;
	{
		int str_erase_begin = 0;							//ディレクトリの0文字目
		int str_erase_end = file_name.find_last_of("\\");	//一番最後のディレクトリを検索

		//不要な文字列の削除処理
		file_name.erase(str_erase_begin, str_erase_end + 1);
	}

	//フォーマット付き文字列の処理
	std::string format_str;
	{
		char buf[1024];
		va_list valist;
		va_start(valist, format);
		vsprintf(buf, format, valist);
		format_str = Format(buf, valist);
		va_end(valist);
	}

	//各、文字列の要素をまとめたもの
	std::string file_name_and_line_num  = "ファイル名：" + file_name	 + "(" + std::to_string(lineNumber) + ")\n";
	std::string function_name			= "関数名    ：" + functionName  + "()\n";
	std::string error_msg				= "エラー内容：" + format_str	 + "\n";

	return std::string(file_name_and_line_num + function_name + error_msg);
}

/*-----------------------------------------------------------------------------
/*　警告メッセージボックスに対するprintf
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
/*　エラーメッセージボックスに対するprintf
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
/* VisualStudioがランタイム時の出力ウィンドウに対するprintf
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
/* コンソールユーザインターフェースに対するprintf
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