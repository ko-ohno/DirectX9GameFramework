/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONManager.cpp] JSON�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FJSON�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "JSONManager.h"

//�G���[���b�Z�[�W�̓��{��|��f�[�^
static const char* jp_error_msg[] = {

    "�G���[�͂���܂���"                                             //!< kParseErrorNone

    , "�h�L�������g�͋�ł��B"                                       //!< kParseErrorDocumentEmpty
    , "�h�L�������g���[�g�́A������`����Ă��܂��B"                 //!< kParseErrorDocumentRootNotSingular                  

    , "�����Ȓl�ł��B"                                               //!< kParseErrorValueInvalid
                                                                          
    , "�I�u�W�F�N�g�����o�[�̖��O������܂���B"                     //!< kParseErrorObjectMissName                 
    , "�I�u�W�F�N�g�E�����o���̌�ɃR����������܂���B"             //!< kParseErrorObjectMissColon
    , "�I�u�W�F�N�g�����o�[�̌�ɃJ���}�܂���'}'������܂���B"      //!< kParseErrorObjectMissCommaOrCurlyBracket  
                                                                          
    , "�z��v�f�̌�ɃJ���}�܂���']'���Ȃ��B"                        //!< kParseErrorArrayMissCommaOrSquareBracket  
                                                                                     
    , "������̌��16�i��������������܂���B"                       //!< kParseErrorStringUnicodeEscapeInvalidHex  
    , "�����񒆂̃T���Q�[�g�E�y�A�������ł��B"                       //!< kParseErrorStringUnicodeSurrogateInvalid 
    , "��������̃G�X�P�[�v�����������ł��B"                         //!< kParseErrorStringEscapeInvalid            
    , "��������Ɉ��p��������܂���B"                               //!< kParseErrorStringMissQuotationMark        
    , "������̃G���R�[�f�B���O�������ł��B"                         //!< kParseErrorStringInvalidEncoding          
                                                                          
    , "���l���傫������double�Ɋi�[�ł��܂���B"                     //!< kParseErrorNumberTooBig        
    , "���l���̒[������������������܂���B"                         //!< kParseErrorNumberMissFraction 
    , "���l�Ɏw��������܂���ł����B"                               //!< kParseErrorNumberMissExponent  
                                                                          
    , "��͂��I�����܂����B"                                         //!< kParseErrorTermination                  
    , "�\���G���[�ł��B"                                             //!< kParseErrorUnspecificSyntaxError
};

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
JSONManager::JSONManager(void)
{

}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
JSONManager::~JSONManager(void)
{
}

/*-----------------------------------------------------------------------------
/* JSON�t�@�C���ւ̃��[�h����
-----------------------------------------------------------------------------*/
bool JSONManager::LoadJSON(const std::string& inFileName, rapidjson::Document& outDoc)
{
	//�ǂݍ��ݐ�p�Ńt�@�C�����J��
	std::ifstream ifs(inFileName.c_str()
				   	 , std::ios::in      //�ǂݎ���p���[�h�ŋN��
				   	 | std::ios::binary  //�o�C�i�����[�h��
				   	 | std::ios::ate);   //�t�@�C���T�C�Y��m�邽�߂ɃV�[�N���t�@�C���̖����ֈړ�
	
	//�t�@�C�����J������(���݂��Ă��邩�H)
	if (!ifs.is_open())
	{
        std::string err_msg = "JSONManager::LoadJSON():JSON�t�@�C�����J���܂���ł����B\n�t�@�C����:" + inFileName;
        MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));
        return false;
	}

    //�V�[�N�̌��݈ʒu�i�����̍��W�j����A�ǂݍ��񂾃t�@�C���̍ő�f�[�^�T�C�Y���擾�B
    std::ifstream::pos_type fileSize = ifs.tellg();

    //�V�[�N�̓ǂݎ����W�̕ύX
    //�t�@�C���i���e�j�̐擪����ɁA�ǂݍ��݂��J�n����悤�Ɏw�肷��B
    ifs.seekg(0, std::ios::beg);

    //�z��̐錾�B�t�@�C���̍ő�f�[�^�T�C�Y+������NULL�������̗]�T��^����
    std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);

    //�ǂݍ��񂾃t�@�C���̏���z��ɃR�s�[
    ifs.read(bytes.data(), static_cast<size_t>(fileSize));

    //RapidJSON��Document�Ƀf�[�^�z���n���āA�z��̏���DOM�Ƃ��č�����́B
    outDoc.Parse(bytes.data());

    //��͌��ʂɃG���[�����邩�H
    bool parse_error = outDoc.HasParseError();
    if (!outDoc.IsObject() || parse_error)
    {
        //�G���[�R�[�h�̕\��
        {
          //�������ɓǂݍ��񂾃t�@�C���̏��̒��ŁA��̓G���[�̌����Bbyte(�o�C�g)�I�t�Z�b�g���W�̎擾
          size_t offset = outDoc.GetErrorOffset();                       
         
          //�G���[�R�[�h�̒萔�ƌ���ݒ�
          JSONManager::LanguageSetting  lang = LanguageSetting::Jp;
          rapidjson::ParseErrorCode     code = outDoc.GetParseError();

          //�G���[�R�[�h�̒萔�ƌ���ݒ�����ƂɁA�G���[���b�Z�[�W��Ԃ�
          const char* error_msg = JSONManager::GetParseErrorMsg(code, lang);

          //�G���[���b�Z�[�W�̏o��
          std::string error_code = "RapidJSON::ParseErrorCode:(" + std::to_string(code) + ")" + std::string(error_msg) + "/";
          std::string error_pos  = "�G���[�Ώۂ̃I�t�Z�b�g���W:byte[" + std::to_string(offset) + "]\n";
          std::string err_msg = "JSONManager::LoadJSON():�t�@�C���̔j�������m�B\n" + error_code + error_pos;
          MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));

        }
        return false;
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* JSON�̍\����̓G���[���b�Z�[�W�̎擾�֐�
-----------------------------------------------------------------------------*/
const char* JSONManager::GetParseErrorMsg(rapidjson::ParseErrorCode inParseErrorCode, const LanguageSetting inSelectLanguage)
{
    //����ݒ�ɂ��X�C�b�`
    switch (inSelectLanguage)
    {
    case LanguageSetting::Jp: 
        return JSONManager::GetParseError_Jp(inParseErrorCode);
        
    case LanguageSetting::En:
        return rapidjson::GetParseError_En(inParseErrorCode);

    default:
        assert("JSONManager::GetParseErrorMsg()�ɁA�K�؂Ȍ���ݒ肪����Ă��܂���B");
        break;
    }

    return nullptr;
}

/*-----------------------------------------------------------------------------
/* ���{��̃G���[���b�Z�[�W�擾�֐�
-----------------------------------------------------------------------------*/
const char* JSONManager::GetParseError_Jp(rapidjson::ParseErrorCode inParseErrorCode)
{
    return  jp_error_msg[static_cast<int>(inParseErrorCode)];
}

/*=============================================================================
/*		End of File
=============================================================================*/