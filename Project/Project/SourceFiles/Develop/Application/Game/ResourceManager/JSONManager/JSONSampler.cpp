/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.cpp] RapidJSON�w���p�[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FRapidJSON�w���p�[�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "JSONSampler.h"

//RapidJSON��JSON�t�@�C���������ɍ\����͂��邽�߂�API

////RapidJSON���̂���
//#include "../External/rapidjson/include/document.h"
////��������
//#include "../External/rapidjson/include/writer.h"
//#include "../External/rapidjson/include/filewritestream.h"  //�C���f���g�E���s�Ȃ�
//#include "../External/rapidjson/include/prettywriter.h"     //�C���f���g�E���s����
////�ǂݍ���
//#include "../External/rapidjson/include/reader.h"
//#include "../External/rapidjson/include/filereadstream.h"
////�G���[�n���h��
//#include "../External/rapidjson/include/error/en.h"

using namespace rapidjson;

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
JSONSampler::JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
JSONSampler::~JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* �ǂݍ��݊֐�
-----------------------------------------------------------------------------*/
void JSONSampler::LoadSamples(void)
{
    //������f�[�^��DOM�ɓn���ĉ�͂��A�ǂݍ��ݕ\�����鏈��
    //JSONSampler::DOMParseSample01();
    //JSONSampler::DOMParseSample02();

    //����������̓��o�͕\�����鏈��
    //JSONSampler::MemoryIOStreamingSample();

    //�t�@�C������̓��o�͕\�����鏈��
    //JSONSampler::FileIOStreamingSample();

    //�\����̓G���[�̏o�͕\���T���v��
    //JSONSampler::ParseErrorSample();

    //Value�̒l���Ƃɍ\����͂���T���v��
    //JSONSampler::GenerateObjectSample();
    //JSONSampler::GenerateArraySample();
    //JSONSampler::GenerateNumberSample();
    JSONSampler::GenerateStringSample();
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_DOM�p�[�X01
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
/* �T���v���֐�_DOM�p�[�X02
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

    //DOM(DocumentObjectModel)�֓n�����f�[�^�̍\����̓G���[�n���h�����O
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
/* �T���v���֐�_����������̓��o�̓X�g���[�~���O
-----------------------------------------------------------------------------*/
void JSONSampler::MemoryIOStreamingSample(void)
{
    const char* json = R"({"name":"value"})";
    Document doc;

    //����if�̕���́A�ǂ���������Ӗ��B����������DOM�֓n���č\����͂���
#if 0
    //�������ւ̓ǂݍ���
    StringStream rs(json);
    doc.ParseStream(rs);    //����������DOM�փp�[�X
#else
    doc.Parse(json);        //����������DOM�֓n���č\�����
#endif // 0

    // �������ݏ���
    StringBuffer ws;
    Writer<StringBuffer> writer(ws); //�o�b�t�@��o�^

    doc.Accept(writer);//DOM����o�b�t�@�֓]��

    const char* result = ws.GetString(); //�o��
    printf("%s\n", result);

}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_�t�@�C������̓��o�̓X�g���[�~���O
-----------------------------------------------------------------------------*/
void JSONSampler::FileIOStreamingSample(void)
{
    FILE* fp;
    char buf[512];
    Document doc;

    // �ǂݍ���
    fp = fopen("json.txt", "rb");
    FileReadStream rs(fp, buf, sizeof(buf));    //�ǂݍ��ݐ�p

    doc.ParseStream(rs);

    fclose(fp);

    // ��������
    fp = fopen("tmp.txt", "wb");
    FileWriteStream ws(fp, buf, sizeof(buf));   //�������ݐ�p

#if 2
    Writer<FileWriteStream> writer(ws);         //�C���f���g�Ȃ�
#else
    PrettyWriter<FileWriteStream> writer(ws);   //�C���f���g����
#endif // 0

    doc.Accept(writer);

    fclose(fp);
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_�\����̓G���[�R�[�h
-----------------------------------------------------------------------------*/
void JSONSampler::ParseErrorSample(void)
{
#if 1
    const char* json = R"({"name":value})";     // �s����(�\��)������
#else
    const char* json = R"({"name":"value"})";   // �L����(�\��)������
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
/* �T���v���֐�_Object�̐�������
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateObjectSample(void)
{
    //DOM��Root�̐����́ADocument�^��錾�A
    //�R���X�g���N�^(kObjectType)��,�����o�֐�SetObject()��
    //Root��Object�^�ł��邱�Ƃ��w�肷��B

    //DOM��Root�𐶐�
    Document doc(kObjectType);   
    //doc.SetObject();

    assert(doc.IsObject());     //DOM��Root��Object�^�ł��邱�Ƃ̊m�F�B

    //object�̐����ɂ���

    //Object�^�̐����́AValue�^��錾�A
    //�R���X�g���N�^(kObjectType)��,�����o�֐�SetObject()��
    //Object�^���w�肷�邱�Ƃɂ���āAObject��Root�𐶐�����
    Value object(kObjectType);
    //object.SetObject();

    assert(object.IsObject()); //�錾����object�����ׂ�BObject�^�ȊO�Ȃ�x����f��

    //object�Ƀ����o�̒ǉ�
    {
        //object�Ƀ����o�̗v�f��ǉ�
        object.AddMember("string", Value("dog"), doc.GetAllocator());
        object.AddMember("int", Value(456), doc.GetAllocator());
        object.AddMember("float", Value(0.1234), doc.GetAllocator());

        //��L��Object�^�̏o�̓f�[�^�i��
        //{
        //    "object" : {
        //        "string" : "dog",
        //        "int" : 456,
        //        "flaot" : 0.1234
        //    }
        //}

#if 0   //�v�f�ւ̍폜���Q�Ƃ��H

        //�v�f�̍폜�ɂ���
        {
            object.AddMember("remove", Value("removable"), doc.GetAllocator());

            const int remove_test_num = 0;
            if (remove_test_num == 0)
            {
                //�P���ɏ���
                object.RemoveMember("remove");
            }
            else if (remove_test_num == 1)
            {
                //�f�[�^�̒�����T���o���č폜����
                Value::MemberIterator itr = object.FindMember("remove");
                if (itr != object.MemberEnd()) {
                    object.RemoveMember(itr);
                    //or obj.EraseMember(itr);
                }
            }
            else if (remove_test_num == 2)
            {
                //�v�f�����ׂď���
                object.RemoveAllMembers();
                object.AddMember("empty", Value("empty"), doc.GetAllocator()); //��������v�f��}��
            }
        }
#else
        //�Q�Ƃ̎d��(DOM�̎Q�Ƃ������悤�ɂł���)
        {
            //DOM�̏ꍇ�́A

            //1.�P�̂ł̎Q��
            const Value& value_1 = object["string"];  //"object"�̒��̃����o"string"���Q��
            printf("1.%s\n", value_1.GetString());

            //2."object"�̒��Ƀ����o"int"�����邩�m�F
            bool exist = object.HasMember("int");  //�����o�̑��݂��m�F
            if (exist) {
                const Value& value_2 = object["int"];
                // ...

                printf("2.%d\n", value_2.GetInt());
            }

            //3.�i2.�̏������Ȍ��Ɂj�C�e���[�^��p���������o�̎Q��
            Value::ConstMemberIterator itr = object.FindMember("float");
            if (itr != object.MemberEnd()) {
                const Value& n = itr->name;
                const Value& v = itr->value;
                printf("3.%s,%f\n", n.GetString(), v.GetFloat());
            }
        }
#endif
    }
    //�v�f�̒u������
    object.AddMember("hoge", Value("hoge"), doc.GetAllocator());
    if (true)
    {
        object["hoge"] = Value("foo");
    }

    //DOM��Root��object��v�f�Ƃ��Ēǉ�
    doc.AddMember("object", object, doc.GetAllocator());

    // �������ݏ���
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //�������w�肵�A�o�b�t�@��o�^

        doc.Accept(writer);                    //DOM����o�b�t�@�֓]��

        const char* result = ws.GetString();   //�o��
        printf("%s\n", result);
    }
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_Array�̐�������
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateArraySample(void)
{
    //DOM��Root�𐶐�
    Document doc(kObjectType);
    //doc.SetObject();
    assert(doc.IsObject());     

    //Array�̐����ɂ���
    Value obj_array(kArrayType);    //�R���X�g���N�^�������o�֐���kArrayType���w��
    //obj_array.SetArray();
    assert(obj_array.IsArray()); //kArrayType�����ׂ�BArray�^�ȊO�Ȃ�x����f��
    
    //�v�f�̒ǉ��ƍ폜
    for (int i = 0; i < 3; i++)
    {
        obj_array.PushBack(Value(i), doc.GetAllocator());
    }
    obj_array.PopBack();

    //�Q��
    assert(obj_array.Size() == 2);
    assert(obj_array[SizeType(0)] == 0);
    assert(obj_array[SizeType(1)] == 1);

    //�u������
    obj_array[SizeType(0)] = 1;

    //�S�폜
    if (false)
    {
        obj_array.Clear();
    }

    //�v�f�̒u������
    doc.AddMember("array", obj_array, doc.GetAllocator());

    // �������ݏ���
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //�������w�肵�A�o�b�t�@��o�^

        doc.Accept(writer);                    //DOM����o�b�t�@�֓]��

        const char* result = ws.GetString();   //�o��
        printf("%s\n", result);
    }
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_Number�̐�������
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateNumberSample(void)
{
    //DOM��Root�𐶐�
    Document doc(kObjectType);
    //doc.SetObject();
    assert(doc.IsObject());

    //Number�̐����ɂ���
    //�R���X�g���N�^�������o�֐���Set**()���g�p
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

    //�Q��
    assert(obj_number1.GetInt()     == 1);
    assert(obj_number2.GetFloat()   == 0.2f);  // GetDouble()�ł��x������Ȃ�
    assert(obj_number3.GetDouble()  == 0.3);   // GetFloat()�ł��x������Ȃ�
    assert(obj_number4.GetUint()    == 4U);
    assert(obj_number5.GetInt64()   == 5LL);
    assert(obj_number6.GetUint64()  == 6LLU);
    assert(obj_number7.GetBool()    == true);

    //DOM��Root�ɗv�f��ǉ�
    doc.AddMember("number1", obj_number1, doc.GetAllocator());
    doc.AddMember("number2", obj_number2, doc.GetAllocator());
    doc.AddMember("number3", obj_number3, doc.GetAllocator());
    doc.AddMember("number4", obj_number4, doc.GetAllocator());
    doc.AddMember("number5", obj_number5, doc.GetAllocator());
    doc.AddMember("number6", obj_number6, doc.GetAllocator());
    doc.AddMember("number7", obj_number7, doc.GetAllocator());

    // �������ݏ���
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //�������w�肵�A�o�b�t�@��o�^

        doc.Accept(writer);                    //DOM����o�b�t�@�֓]��

        const char* result = ws.GetString();   //�o��
        printf("%s\n", result);
    }
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_String�̐�������
-----------------------------------------------------------------------------*/
void JSONSampler::GenerateStringSample(void)
{
    //DOM��Root�𐶐�
    Document doc(kObjectType);
    //doc.SetObject();
    assert(doc.IsObject());

    //String�̐����ɂ���
    //�R���X�g���N�^�������o�֐��ŕ�������w��
    Value obj_string1("hoge");    
   // obj_string.SetString("hoge");
    assert(obj_string1.IsString()); //string�����ׂ�Bstring�^�ȊO�Ȃ�x����f��

    //string�̕���
    Value obj_string2;
    {
        char buf[16];

        sprintf(buf, "%s-%s", "copy", "string");
        obj_string2.SetString(buf, doc.GetAllocator());// copy-string
        const char* result = obj_string2.GetString();   //�o��
        printf("%s\n", result);
    }

    //�|�C���^�ւ̎Q��
    const char* a = obj_string2.GetString();
    assert(obj_string2 == "copy-string");
    printf("%s\n", a);

    //�v�f�̒u������
    doc.AddMember("string1", obj_string1, doc.GetAllocator());
    doc.AddMember("string2", obj_string2, doc.GetAllocator());

    // �������ݏ���
    {
        StringBuffer ws;
        PrettyWriter<StringBuffer> writer(ws); //�������w�肵�A�o�b�t�@��o�^

        doc.Accept(writer);                    //DOM����o�b�t�@�֓]��

        const char* result = ws.GetString();   //�o��
        printf("%s\n", result);
    }
}

/*=============================================================================
/*		End of File
=============================================================================*/