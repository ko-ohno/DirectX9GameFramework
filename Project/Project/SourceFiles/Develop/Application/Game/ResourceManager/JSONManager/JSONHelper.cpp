/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONHelper.cpp] RapidJSONヘルパークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：RapidJSONヘルパークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "JSONHelper.h"

//RapidJSONはJSONファイルを高速に構文解析するためのAPI
using namespace rapidjson;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
JSONHelper::JSONHelper(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
JSONHelper::~JSONHelper(void)
{
}

/*-----------------------------------------------------------------------------
/* JSONのInt型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetInt(const rapidjson::Value& inObject, const char* inPropertyName, int& outInt)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、整数型であることを確認
	auto& property = itr->value;
	if (!property.IsInt())
	{
		return false;
	}

	//プロパティの値を出力
	outInt = property.GetInt();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのFloat型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetFloat(const rapidjson::Value& inObject, const char* inPropertyName, float& outFloat)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、実数型であることを確認
	auto& property = itr->value;
	if (!property.IsFloat())
	{
		return false;
	}

	//プロパティの値を出力
	outFloat = property.GetFloat();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのDouble型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetDouble(const rapidjson::Value& inObject, const char* inPropertyName, double& outDouble)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、倍精度実数型であることを確認
	auto& property = itr->value;
	if (!property.IsDouble())
	{
		return false;
	}

	//プロパティの値を出力
	outDouble = property.GetDouble();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのString型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetString(const rapidjson::Value& inObject, const char* inPropertyName, std::string& outStr)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、文字列型であることを確認
	auto& property = itr->value;
	if (!property.IsString())
	{
		return false;
	}

	//プロパティの値を出力
	outStr = property.GetString();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのBool型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetBool(const rapidjson::Value& inObject, const char* inPropertyName, bool& outBool)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、論理型であることを確認
	auto& property = itr->value;
	if (!property.IsBool())
	{
		return false;
	}

	//プロパティの値を出力
	outBool = property.GetBool();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのInt型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, int value)
{
	rapidjson::Value v(value);
	assert(v.IsInt());
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSONのFloat型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, float value)
{
	rapidjson::Value v(value);
	assert(v.IsFloat());
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSONのDouble型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddDouble(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, double value)
{
	rapidjson::Value v(value);
	assert(v.IsDouble());
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSONのString型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddString(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, const std::string& value)
{
	rapidjson::Value v;
	v.SetString(value.c_str()
			   , static_cast<rapidjson::SizeType>(value.length())
			   , alloc);
	assert(v.IsString());
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSONのBool型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddBool(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, bool value)
{
	rapidjson::Value v(value);
	assert(v.IsString());
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*=============================================================================
/*		End of File
=============================================================================*/