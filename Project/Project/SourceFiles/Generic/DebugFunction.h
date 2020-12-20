/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[DebugSystem.h] デバッグシステム
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：デバッグシステム
=============================================================================*/
#ifndef DEBUG_SYSTEM_H_
#define	DEBUG_SYSTEM_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* 構造体
-------------------------------------*/



/*--- マクロ定義 ---*/

// 組み込みマクロの展開先を制御するために、文字列操作をするための関数を、マクロ定義に内包させた。

 /*! @brief  OUTPUT_ERROR_MSG()は,デバッグ用のエラーメッセージ文字列を生成します。
 //  @param [in]パラメータには、char*型配列か、std::string型を渡してください。
 //  @return OUTPUT_ERROR_MSG()は、このマクロの呼び出し先の"ソースファイル名" と "行番号" と "関数名" および、
 // このマクロの"引数に定義したエラー内容の文字列" を含む std::string型の文字列データを出力します。
 */
#define OUTPUT_ERROR_MSG(errorMsg) \
(\
	DebugFunction::OutputErrorString(errorMsg, __FILE__, __LINE__, __FUNCTION__) \
);
//#define OUTPUT_ERROR_MSG(errorMsg, ...) (DebugFunction::OutputErrorString(errorMsg, __FILE__, __LINE__, __FUNCTION__));

/*-------------------------------------
/* デバッグシステム
-------------------------------------*/
namespace DebugFunction
{
	// @brief OutputErrorString()は、デバッグ用のエラーメッセージ文字列を生成します。
	// @param [in] エラー内容となる "文字列データ" を入力。
	// @param [in] この関数の呼び出し先の "ファイル名" を入力。
	// @param [in] この関数の呼び出し先の "行番号" を入力。
	// @param [in] この関数を呼び出し先の "関数名" を入力
	// @return すべてのパラメータを結合した、デバッグ用のエラーメッセージ文字列を生成します。
	std::string OutputErrorString(std::string inErrorMsg
						         , std::string inFileName
						         , int inLineNumber
						         , std::string inFunctionName);

	//あとで実装する
	//マクロは￥で改行できる

	//void RuntimeOutputDebugString(const char* format, ...);



	// @brief コンソール画面にフォーマット付き文字列を表示
	// @param format フォーマット  (%dとか%fとかの)
	// @param 可変長変数
	// @remarks この関数はデバッグ用です、デバッグ時にしか動作しません
	void DebugOutputFormatString(const char* format, ...);

};


#endif //DEBUG_SYSTEM_H_
/*=============================================================================
/*		End of File
=============================================================================*/
