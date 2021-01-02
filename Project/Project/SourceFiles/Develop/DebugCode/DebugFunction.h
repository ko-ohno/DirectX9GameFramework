/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugFunction.h] デバッグ関数
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デバッグ関数
=============================================================================*/
#ifndef DEBUG_FUNCTION_H_
#define	DEBUG_FUNCTION_H_


/*--- インクルードファイル ---*/

/*-------------------------------------
/* 構造体
-------------------------------------*/


/*--- マクロ定義 ---*/

// 組み込みマクロの展開先を制御するために、文字列操作をするための関数を、マクロ定義に内包させた。

 /*! @brief このマクロは、「呼び出し先の」"ファイル名"と"行番号"、"関数名"を特定し、第一引数に指定したフォーマット付き文字列を生成します
//  @param [in] format フォーマット  (%dとか%fとかの)
//  @param [in] このパラメータには、char*型か、std::string型などの文字列を渡してください。
//  @return このマクロの呼び出し先の"ソースファイル名" と "行番号" と "関数名" および、"第一引数に指定したフォーマット付き文字列" を複合したstd::string型の文字列データを出力します。
*/
#define OUTPUT_FORMAT_STRING(format, ...) ( DebugFunction::OutputFormatString(__FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__) )

/*-------------------------------------
/* デバッグ関数
-------------------------------------*/
namespace DebugFunction
{
	//std::string型でフォーマット付き文字列を扱うためのテンプレート関数
	template <typename ... Args>
	std::string Format(const std::string& fmt, Args ... args)
	{
		size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
		std::vector<char> buf(len + 1);
		std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
		return std::string(&buf[0], &buf[0] + len);
	}

	// @brief デバッグ用のエラーメッセージ用のフォーマット付き文字列生成します。
	// @param [in] format フォーマット  (%dとか%fとかの)
	// @param [in] この関数の呼び出し先の "ファイル名" を入力。
	// @param [in] この関数の呼び出し先の "行番号" を入力。
	// @param [in] この関数を呼び出し先の "関数名" を入力
	// @return すべてのパラメータを結合した、デバッグ用のエラーメッセージ文字列を生成します。
	std::string OutputFormatString(const std::string& fileName, int lineNumber, const std::string& functionName, const char* format, ...);

	// @brief ワーニング処理に対してはこの関数を使う。メッセージボックスにフォーマット付き文字列を表示
	// @param [in] format フォーマット  (%dとか%fとかの)
	// @param [in] 可変長変数
	// @remarks この関数はパラメータに指定された警告メッセージを表示します。
	void PrintfToWarningMessageBox(const char* format, ...);

	// @brief エラー処理に対してはこの関数を使う。assert()にフォーマット付き文字列を表示
	// @param [in] format フォーマット  (%dとか%fとかの)
	// @param [in] 可変長変数
	// @remarks この関数はパラメータに指定されたエラーメッセージを表示します。
	void PrintfToErrorMessageBox(const char* format, ...);

	// @brief VisualStudioがランタイム時の出力ウィンドウにフォーマット付き文字列を表示
	// @param [in] format フォーマット  (%dとか%fとかの)
	// @param [in] 可変長変数
	// @remarks この関数はデバッグ用です、デバッグ時にしか動作しません
	void PrintfToIDERuntimeOutputWindow(const char* format, ...);


	// @brief コマンドライン インターフェース にフォーマット付き文字列を表示
	// @param [in] format フォーマット  (%dとか%fとかの)
	// @param [in] 可変長変数
	// @remarks この関数はデバッグ用です、デバッグ時にしか動作しません
	void PrintfToCUIWindow(const char* format, ...);

};


#endif //DEBUG_FUNCTION_H_
/*=============================================================================
/*		End of File
=============================================================================*/
