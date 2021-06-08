/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.cpp] RapidJSONヘルパークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：RapidJSONヘルパークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "JSONSampler.h"

//RapidJSONはJSONファイルを高速に構文解析するためのAPI

////RapidJSONそのもの
//#include "../External/rapidjson/include/document.h"
////書き込み
//#include "../External/rapidjson/include/writer.h"
//#include "../External/rapidjson/include/filewritestream.h"  //インデント・改行なし
//#include "../External/rapidjson/include/prettywriter.h"     //インデント・改行あり
////読み込み
//#include "../External/rapidjson/include/reader.h"
//#include "../External/rapidjson/include/filereadstream.h"
////エラーハンドル
//#include "../External/rapidjson/include/error/en.h"

using namespace rapidjson;

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
JSONSampler::JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
JSONSampler::~JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* 読み込み関数
-----------------------------------------------------------------------------*/
void JSONSampler::LoadSamples(void)
{
    //文字列データをDOMに渡して解析し、読み込み表示する処理
    //JSONSampler::DOMParseSample01();
    //JSONSampler::DOMParseSample02();

    //メモリからの入出力表示する処理
    //JSONSampler::MemoryIOStreamingSample();

    //ファイルからの入出力表示する処理
    //JSONSampler::FileIOStreamingSample();

    //構文解析エラーの出力表示サンプル
    //JSONSampler::ParseErrorSample();

    //Valueの値ごとに構文解析するサンプル
    //JSONSampler::GenerateObjectSample();
    //JSONSampler::GenerateArraySample();
    //JSONSampler::GenerateNumberSample();
    JSONSampler::GenerateStringSample();
}

/*-----------------------------------------------------------------------------
/* サンプル関数_DOMパース01
-----------------------------------------------------------------------------*/
void JSONSampler::DOMParseSample01(void)
{
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
}

/*-----------------------------------------------------------------------------
/* サンプル関数_DOMパース02
-----------------------------------------------------------------------------*/
void JSONSampler::DOMParseSample02(void)
{
    const char* s_json = R"(
    {
        "string" : "foo",
        "number" : 123,
        "array" : [
            0,
            1,
            2,
            3
        ],
        "object" : {
            "v0" : "bar",
            "v1" : 456,
            "v2" : 0.123
        }
    }
    )";

    Document doc;

    //DOM(DocumentObjectModel)へ渡したデータの構文解析エラーハンドリング
    doc.Parse(s_json);
    bool error = doc.HasParseError();
    if (error) {
        printf("parse error\n");
        return;
    }

    // string
    {
        const char* v = doc["string"].GetString();
        printf("string = %s\n", v);
    }

    // number
    {
        int v = doc["number"].GetInt();
        printf("number = %d\n", v);
    }

    // array
    {
        const Value& a = doc["array"];
        SizeType num = a.Size();

        for (SizeType i = 0; i < num; i++) {
            int v = a[i].GetInt();
            printf("array[%d] = %d\n", i, v);
        }
    }

    // object
    {
        const Value& o = doc["object"];

        // enumerate members in object
        for (Value::ConstMemberIterator itr = o.MemberBegin();
            itr != o.MemberEnd(); itr++)
        {
            const char* name = itr->name.GetString();
            const Value& value = itr->value;
            Type type = value.GetType();

            printf("%s = ", name);
            switch (type) {
            case kStringType:
                printf("%s", value.GetString());
                break;

            case kNumberType:
                if (value.IsDouble())
                    printf("%f", value.GetDouble());
                else
                    printf("%d", value.GetInt());
                break;

            default:
                printf("(unknown type)");
                break;
            }
            printf("\n");
        }
    }
}

/*-----------------------------------------------------------------------------
/* サンプル関数_メモリからの入出力ストリーミング
-----------------------------------------------------------------------------*/
void JSONSampler::MemoryIOStreamingSample(void)
{
    const char* json = R"({"name":"value"})";
    Document doc;

    //このifの分岐は、どちらも同じ意味。メモリからDOMへ渡して構文解析する
#if 0
    //メモリへの読み込み
    StringStream rs(json);
    doc.ParseStream(rs);    //メモリからDOMへパース
#else
    doc.Parse(json);        //メモリからDOMへ渡して構文解析
#endif // 0

    // 書き込み処理
    StringBuffer ws;
    Writer<StringBuffer> writer(ws); //バッファを登録

    doc.Accept(writer);//DOMからバッファへ転送

    const char* result = ws.GetString(); //出力
    printf("%s\n", result);

}

/*-----------------------------------------------------------------------------
/* サンプル関数_ファイルからの入出力ストリーミング
-----------------------------------------------------------------------------*/
void JSONSampler::FileIOStreamingSample(void)
{
    FILE* fp;
    char buf[512];
    Document doc;

    // 読み込み
    fp = fopen("json.txt", "rb");
    FileReadStream rs(fp, buf, sizeof(buf));    //読み込み専用

    doc.ParseStream(rs);

    fclose(fp);

    // 書き込み
    fp = fopen("tmp.txt", "wb");
    FileWriteStream ws(fp, buf, sizeof(buf));   //書き込み専用

#if 2
    Writer<FileWriteStream> writer(ws);         //インデントなし
#else
    PrettyWriter<FileWriteStream> writer(ws);   //インデントあり
#endif // 0

    doc.Accept(writer);

    fclose(fp);
}

/*-----------------------------------------------------------------------------
/* サンプル関数_構文解析エラーコード
-----------------------------------------------------------------------------*/
void JSONSampler::ParseErrorSample(void)
{
#if 1
    const char* json = R"({"name":value})";     // 不正な(構文)文字列
#else
    const char* json = R"({"name":"value"})";   // 有効な(構文)文字列
#endif // 0

    Document doc;

    doc.Parse(json);

    bool error = doc.HasParseError();
    if (error) {
        size_t offset = doc.GetErrorOffset();
        ParseErrorCode code = doc.GetParseError();
        const char* msg = GetParseError_En(code);

        printf("%d:%d(%s)\n", offset, code, msg);
    }
}

/*-----------------------------------------------------------------------------
/* サンプル関数_Objectの生成処理
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateObjectSample(void)
{
    //DOMのRootの生成は、Document型を宣言、
    //コンストラクタ(kObjectType)か,メンバ関数SetObject()で
    //RootがObject型であることを指定する。

    //DOMのRootを生成
    Document doc(kObjectType);   
    //doc.SetObject();

    assert(doc.IsObject());     //DOMのRootがObject型であることの確認。

    //objectの生成について

    //Object型の生成は、Value型を宣言、
    //コンストラクタ(kObjectType)か,メンバ関数SetObject()で
    //Object型を指定することによって、ObjectのRootを生成する
    Value object(kObjectType);
    //object.SetObject();

    assert(object.IsObject()); //宣言したobjectか調べる。Object型以外なら警告を吐く

    //objectにメンバの追加
    {
        //objectにメンバの要素を追加
        object.AddMember("string", Value("dog"), doc.GetAllocator());
        object.AddMember("int", Value(456), doc.GetAllocator());
        object.AddMember("float", Value(0.1234), doc.GetAllocator());

        //上記のObject型の出力データ（例
        //{
        //    "object" : {
        //        "string" : "dog",
        //        "int" : 456,
        //        "flaot" : 0.1234
        //    }
        //}

#if 0   //要素への削除か参照か？

        //要素の削除について
        {
            object.AddMember("remove", Value("removable"), doc.GetAllocator());

            const int remove_test_num = 0;
            if (remove_test_num == 0)
            {
                //単純に消す
                object.RemoveMember("remove");
            }
            else if (remove_test_num == 1)
            {
                //データの中から探し出して削除する
                Value::MemberIterator itr = object.FindMember("remove");
                if (itr != object.MemberEnd()) {
                    object.RemoveMember(itr);
                    //or obj.EraseMember(itr);
                }
            }
            else if (remove_test_num == 2)
            {
                //要素をすべて消す
                object.RemoveAllMembers();
                object.AddMember("empty", Value("empty"), doc.GetAllocator()); //空を示す要素を挿入
            }
        }
#else
        //参照の仕方(DOMの参照も同じようにできる)
        {
            //DOMの場合は、

            //1.単体での参照
            const Value& value_1 = object["string"];  //"object"の中のメンバ"string"を参照
            printf("1.%s\n", value_1.GetString());

            //2."object"の中にメンバ"int"があるか確認
            bool exist = object.HasMember("int");  //メンバの存在を確認
            if (exist) {
                const Value& value_2 = object["int"];
                // ...

                printf("2.%d\n", value_2.GetInt());
            }

            //3.（2.の処理を簡潔に）イテレータを用いたメンバの参照
            Value::ConstMemberIterator itr = object.FindMember("float");
            if (itr != object.MemberEnd()) {
                const Value& n = itr->name;
                const Value& v = itr->value;
                printf("3.%s,%f\n", n.GetString(), v.GetFloat());
            }
        }
#endif
    }
    //要素の置き換え
    object.AddMember("hoge", Value("hoge"), doc.GetAllocator());
    if (true)
    {
        object["hoge"] = Value("foo");
    }

    //DOMのRootにobjectを要素として追加
    doc.AddMember("object", object, doc.GetAllocator());

    // 書き込み処理
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //書式を指定し、バッファを登録

        doc.Accept(writer);                    //DOMからバッファへ転送

        const char* result = ws.GetString();   //出力
        printf("%s\n", result);
    }
}

/*-----------------------------------------------------------------------------
/* サンプル関数_Arrayの生成処理
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateArraySample(void)
{
    //DOMのRootを生成
    Document doc(kObjectType);
    //doc.SetObject();
    assert(doc.IsObject());     

    //Arrayの生成について
    Value obj_array(kArrayType);    //コンストラクタかメンバ関数でkArrayTypeを指定
    //obj_array.SetArray();
    assert(obj_array.IsArray()); //kArrayTypeか調べる。Array型以外なら警告を吐く
    
    //要素の追加と削除
    for (int i = 0; i < 3; i++)
    {
        obj_array.PushBack(Value(i), doc.GetAllocator());
    }
    obj_array.PopBack();

    //参照
    assert(obj_array.Size() == 2);
    assert(obj_array[SizeType(0)] == 0);
    assert(obj_array[SizeType(1)] == 1);

    //置き換え
    obj_array[SizeType(0)] = 1;

    //全削除
    if (false)
    {
        obj_array.Clear();
    }

    //要素の置き換え
    doc.AddMember("array", obj_array, doc.GetAllocator());

    // 書き込み処理
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //書式を指定し、バッファを登録

        doc.Accept(writer);                    //DOMからバッファへ転送

        const char* result = ws.GetString();   //出力
        printf("%s\n", result);
    }
}

/*-----------------------------------------------------------------------------
/* サンプル関数_Numberの生成処理
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateNumberSample(void)
{
    //DOMのRootを生成
    Document doc(kObjectType);
    //doc.SetObject();
    assert(doc.IsObject());

    //Numberの生成について
    //コンストラクタかメンバ関数でSet**()を使用
    Value obj_number1(1);       // int
    Value obj_number2(0.2f);    // float
    Value obj_number3(0.3);     // double
    Value obj_number4(4U);      // unsigned int
    Value obj_number5(5LL);     // 64bit_int
    Value obj_number6(6LLU);    // unsigned 64bit_int
    Value obj_number7(true);    // bool

    //obj_number1.SetInt(1);          // int
    //obj_number2.SetFloat(0.2f);     // float
    //obj_number3.SetDouble(0.3);     // double
    //obj_number4.SetUint(4U);        // unsigned int
    //obj_number5.SetInt64(5LL);      // 64bit_int
    //obj_number6.SetUint64(6LLU);    // unsigned 64bit_int
    //obj_number7.SetBool(true);      // bool

    //参照
    assert(obj_number1.GetInt()     == 1);
    assert(obj_number2.GetFloat()   == 0.2f);  // GetDouble()でも警告されない
    assert(obj_number3.GetDouble()  == 0.3);   // GetFloat()でも警告されない
    assert(obj_number4.GetUint()    == 4U);
    assert(obj_number5.GetInt64()   == 5LL);
    assert(obj_number6.GetUint64()  == 6LLU);
    assert(obj_number7.GetBool()    == true);

    //DOMのRootに要素を追加
    doc.AddMember("number1", obj_number1, doc.GetAllocator());
    doc.AddMember("number2", obj_number2, doc.GetAllocator());
    doc.AddMember("number3", obj_number3, doc.GetAllocator());
    doc.AddMember("number4", obj_number4, doc.GetAllocator());
    doc.AddMember("number5", obj_number5, doc.GetAllocator());
    doc.AddMember("number6", obj_number6, doc.GetAllocator());
    doc.AddMember("number7", obj_number7, doc.GetAllocator());

    // 書き込み処理
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //書式を指定し、バッファを登録

        doc.Accept(writer);                    //DOMからバッファへ転送

        const char* result = ws.GetString();   //出力
        printf("%s\n", result);
    }
}

/*-----------------------------------------------------------------------------
/* サンプル関数_Stringの生成処理
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateStringSample(void)
{
    //DOMのRootを生成
    Document doc(kObjectType);
    //doc.SetObject();
    assert(doc.IsObject());

    //Stringの生成について
    //コンストラクタかメンバ関数で文字列を指定
    Value obj_string1("hoge");    
   // obj_string.SetString("hoge");
    assert(obj_string1.IsString()); //stringか調べる。string型以外なら警告を吐く

    //stringの複製
    Value obj_string2;
    {
        char buf[16];

        sprintf(buf, "%s-%s", "copy", "string");
        obj_string2.SetString(buf, doc.GetAllocator());// copy-string
        const char* result = obj_string2.GetString();   //出力
        printf("%s\n", result);
    }

    //ポインタへの参照
    const char* a = obj_string2.GetString();
    assert(obj_string2 == "copy-string");
    printf("%s\n", a);

    //要素の置き換え
    doc.AddMember("string1", obj_string1, doc.GetAllocator());
    doc.AddMember("string2", obj_string2, doc.GetAllocator());

    // 書き込み処理
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //書式を指定し、バッファを登録

        doc.Accept(writer);                    //DOMからバッファへ転送

        const char* result = ws.GetString();   //出力
        printf("%s\n", result);
    }
}

/*=============================================================================
/*		End of File
=============================================================================*/