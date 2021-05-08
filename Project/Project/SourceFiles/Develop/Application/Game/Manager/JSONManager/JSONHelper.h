/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONHelper.h] RapidJSONヘルパークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：JSON操作ヘルパークラス
=============================================================================*/
#ifndef JSON_HELPER_H_
#define	JSON_HELPER_H_

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* RapidJSONヘルパークラス
-------------------------------------*/
class JSONHelper
{
private:
	JSONHelper(void);

public:
	~JSONHelper(void);

	////////////////////////////////////////////////////////////////////////////////////
	/*==================== JSONオブジェクトのプロパティGet関数群 ====================*/
	////////////////////////////////////////////////////////////////////////////////////

	// GetInt()は,成功した場合に true を返します．
	// 1番目のパラメータには、JSONオブジェクトを入力。
	// 2番目のパラメータには、オブジェクト内のプロパティ名を入力。
	// 3番目のパラメータにオブジェクト内のプロパティから取得する値が出力されます。
	// さらに、プロパティが見つからなかった場合、戻り値を変更しないことが保証されています。
	static bool GetInt(const rapidjson::Value& inObject, const char* inPropertyName, int& outInt);
	
	// GetFloat()は,成功した場合に true を返します．
	// 1番目のパラメータには、JSONオブジェクトを入力。
	// 2番目のパラメータには、オブジェクト内のプロパティ名を入力。
	// 3番目のパラメータにオブジェクト内のプロパティから取得する値が出力されます。
	// さらに、プロパティが見つからなかった場合、戻り値を変更しないことが保証されています。
	static bool GetFloat(const rapidjson::Value& inObject, const char* inPropertyName, float& outFloat);

	// GetDouble()は,成功した場合に true を返します．
	// 1番目のパラメータには、JSONオブジェクトを入力。
	// 2番目のパラメータには、オブジェクト内のプロパティ名を入力。
	// 3番目のパラメータにオブジェクト内のプロパティから取得する値が出力されます。
	// さらに、プロパティが見つからなかった場合、戻り値を変更しないことが保証されています。
	static bool GetDouble(const rapidjson::Value& inObject, const char* inPropertyName, double& outDouble);

	// GetString()は,成功した場合に true を返します．
	// 1番目のパラメータには、JSONオブジェクトを入力。
	// 2番目のパラメータには、オブジェクト内のプロパティ名を入力。
	// 3番目のパラメータにオブジェクト内のプロパティから取得する値が出力されます。
	// さらに、プロパティが見つからなかった場合、戻り値を変更しないことが保証されています。
	static bool GetString(const rapidjson::Value& inObject, const char* inPropertyName, std::string& outStr);


	// GetBool()は,成功した場合に true を返します．
	// 1番目のパラメータには、JSONオブジェクトを入力。
	// 2番目のパラメータには、オブジェクト内のプロパティ名を入力。
	// 3番目のパラメータにオブジェクト内のプロパティから取得する値が出力されます。
	// さらに、プロパティが見つからなかった場合、戻り値を変更しないことが保証されています。
	static bool GetBool(const rapidjson::Value& inObject, const char* inPropertyName, bool& outBool);


	////////////////////////////////////////////////////////////////////////////////////
	/*==================== JSONオブジェクトのプロパティSet関数群 ====================*/
	////////////////////////////////////////////////////////////////////////////////////


	// AddInt()は,JSONのDocumentに、int型のデータメンバを追加します。
	// 1番目のパラメータには、JSONのDocumentを入力。
	// 2番目のパラメータには、JSONオブジェクトを入力。
	// 3番目のパラメータには、プロパティ名を命名して入力。
	// 4番目のパラメータには、命名したプロパティが含むint型の"値"を入力。
	// さらに、入力した値がint型でなかった場合、警告を発行します。
	static void AddInt(rapidjson::Document::AllocatorType& alloc
					  , rapidjson::Value& inObject
					  , const char* inPropertyName
					  , int value);

	// AddFloat()は,JSONのDocumentに、float型のデータメンバを追加します。
	// 1番目のパラメータには、JSONのDocumentを入力。
	// 2番目のパラメータには、JSONオブジェクトを入力。
	// 3番目のパラメータには、プロパティ名を命名して入力。
	// 4番目のパラメータには、命名したプロパティが含むfloat型の"値"を入力。
	// さらに、入力した値がfloat型でなかった場合、警告を発行します。
	static void AddFloat(rapidjson::Document::AllocatorType& alloc
						, rapidjson::Value& inObject
						, const char* inPropertyName
						, float value);


	// AddDouble()は,JSONのDocumentに、float型のデータメンバを追加します。
	// 1番目のパラメータには、JSONのDocumentを入力。
	// 2番目のパラメータには、JSONオブジェクトを入力。
	// 3番目のパラメータには、プロパティ名を命名して入力。
	// 4番目のパラメータには、命名したプロパティが含むdouble型の"値"を入力。
	// さらに、入力した値がdouble型でなかった場合、警告を発行します。
	static void AddDouble(rapidjson::Document::AllocatorType& alloc
						 , rapidjson::Value& inObject
						 , const char* inPropertyName
						 , double value);


	// AddString()は,JSONのDocumentに、string型のデータメンバを追加します。
	// 1番目のパラメータには、JSONのDocumentを入力。
	// 2番目のパラメータには、JSONオブジェクトを入力。
	// 3番目のパラメータには、プロパティ名を命名して入力。
	// 4番目のパラメータには、命名したプロパティが含むstring型の"値"を入力。
	// さらに、入力した値がstring型でなかった場合、警告を発行します。
	static void AddString(rapidjson::Document::AllocatorType& alloc
						 , rapidjson::Value& inObject
						 , const char* inPropertyName
						 , const std::string& value);

	// AddBool()は,JSONのDocumentに、bool型のデータメンバを追加します。
	// 1番目のパラメータには、JSONのDocumentを入力。
	// 2番目のパラメータには、JSONオブジェクトを入力。
	// 3番目のパラメータには、プロパティ名を命名して入力。
	// 4番目のパラメータには、命名したプロパティが含むbool型の"値"を入力。
	// さらに、入力した値がbool型でなかった場合、警告を発行します。
	static void AddBool(rapidjson::Document::AllocatorType& alloc
					   , rapidjson::Value& inObject
					   , const char* inPropertyName
					   , bool value);

};

#endif //JSON_HELPER_H_
/*=============================================================================
/*		End of File
=============================================================================*/