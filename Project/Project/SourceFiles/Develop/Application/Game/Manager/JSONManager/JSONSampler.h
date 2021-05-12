/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.h] RapidJSONサンプラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：JSON操作サンプラークラス
=============================================================================*/
#ifndef JSON_SAMPLER_H_
#define	JSON_SAMPLER_H_

/*--- インクルードファイル ---*/

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/

//Qiita記事
//https://qiita.com/k2ymg/items/eef3b15eaa27a89353ab

//RapidJSON公式ドキュメント
//https://rapidjson.org/index.html

//上記のURLのQiitaの記事と公式ドキュメントを解読しながら実装

/*-------------------------------------
/* RapidJSONサンプラークラス
-------------------------------------*/
class JSONSampler
{
private:
	JSONSampler(void);

public:
	~JSONSampler(void);

	//サンプルの呼び出し
	static void LoadSamples(void);

	//文字列データをDOMに渡して構文解析、読み込み表示する処理
	static void DOMParseSample01(void);
	static void DOMParseSample02(void);

	//メモリからの入出力ストリーム
	static void MemoryIOStreamingSample(void);

	//ファイルからの入出力ストリーム
	static void FileIOStreamingSample(void);

	//構文解析エラーコードの出力
	static void ParseErrorSample(void);

	//Valueの型ごとに構文解析するサンプル

	//Object
	static void GenerateObjectSample(void);
	//Array
	static void GenerateArraySample(void);
	//Number
	static void GenerateNumberSample(void);
	//String
	static void GenerateStringSample(void);
};

#endif //JSON_SAMPLER_H_
/*=============================================================================
/*		End of File
=============================================================================*/