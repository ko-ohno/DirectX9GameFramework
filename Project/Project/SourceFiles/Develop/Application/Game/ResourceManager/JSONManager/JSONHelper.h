/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONHelper.h] RapidJSON�w���p�[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FJSON����w���p�[�N���X
=============================================================================*/
#ifndef JSON_HELPER_H_
#define	JSON_HELPER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* RapidJSON�w���p�[�N���X
-------------------------------------*/
class JSONHelper
{
private:
	JSONHelper(void);

public:
	~JSONHelper(void);

	////////////////////////////////////////////////////////////////////////////////////
	/*==================== JSON�I�u�W�F�N�g�̃v���p�e�BGet�֐��Q ====================*/
	////////////////////////////////////////////////////////////////////////////////////

	// GetInt()��,���������ꍇ�� true ��Ԃ��܂��D
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́A�I�u�W�F�N�g���̃v���p�e�B������́B
	// 3�Ԗڂ̃p�����[�^�ɃI�u�W�F�N�g���̃v���p�e�B����擾����l���o�͂���܂��B
	// ����ɁA�v���p�e�B��������Ȃ������ꍇ�A�߂�l��ύX���Ȃ����Ƃ��ۏ؂���Ă��܂��B
	static bool GetInt(const rapidjson::Value& inObject, const char* inPropertyName, int& outInt);
	
	// GetFloat()��,���������ꍇ�� true ��Ԃ��܂��D
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́A�I�u�W�F�N�g���̃v���p�e�B������́B
	// 3�Ԗڂ̃p�����[�^�ɃI�u�W�F�N�g���̃v���p�e�B����擾����l���o�͂���܂��B
	// ����ɁA�v���p�e�B��������Ȃ������ꍇ�A�߂�l��ύX���Ȃ����Ƃ��ۏ؂���Ă��܂��B
	static bool GetFloat(const rapidjson::Value& inObject, const char* inPropertyName, float& outFloat);

	// GetDouble()��,���������ꍇ�� true ��Ԃ��܂��D
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́A�I�u�W�F�N�g���̃v���p�e�B������́B
	// 3�Ԗڂ̃p�����[�^�ɃI�u�W�F�N�g���̃v���p�e�B����擾����l���o�͂���܂��B
	// ����ɁA�v���p�e�B��������Ȃ������ꍇ�A�߂�l��ύX���Ȃ����Ƃ��ۏ؂���Ă��܂��B
	static bool GetDouble(const rapidjson::Value& inObject, const char* inPropertyName, double& outDouble);

	// GetString()��,���������ꍇ�� true ��Ԃ��܂��D
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́A�I�u�W�F�N�g���̃v���p�e�B������́B
	// 3�Ԗڂ̃p�����[�^�ɃI�u�W�F�N�g���̃v���p�e�B����擾����l���o�͂���܂��B
	// ����ɁA�v���p�e�B��������Ȃ������ꍇ�A�߂�l��ύX���Ȃ����Ƃ��ۏ؂���Ă��܂��B
	static bool GetString(const rapidjson::Value& inObject, const char* inPropertyName, std::string& outStr);


	// GetBool()��,���������ꍇ�� true ��Ԃ��܂��D
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́A�I�u�W�F�N�g���̃v���p�e�B������́B
	// 3�Ԗڂ̃p�����[�^�ɃI�u�W�F�N�g���̃v���p�e�B����擾����l���o�͂���܂��B
	// ����ɁA�v���p�e�B��������Ȃ������ꍇ�A�߂�l��ύX���Ȃ����Ƃ��ۏ؂���Ă��܂��B
	static bool GetBool(const rapidjson::Value& inObject, const char* inPropertyName, bool& outBool);


	////////////////////////////////////////////////////////////////////////////////////
	/*==================== JSON�I�u�W�F�N�g�̃v���p�e�BSet�֐��Q ====================*/
	////////////////////////////////////////////////////////////////////////////////////


	// AddInt()��,JSON��Document�ɁAint�^�̃f�[�^�����o��ǉ����܂��B
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON��Document����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 3�Ԗڂ̃p�����[�^�ɂ́A�v���p�e�B���𖽖����ē��́B
	// 4�Ԗڂ̃p�����[�^�ɂ́A���������v���p�e�B���܂�int�^��"�l"����́B
	// ����ɁA���͂����l��int�^�łȂ������ꍇ�A�x���𔭍s���܂��B
	static void AddInt(rapidjson::Document::AllocatorType& alloc
					  , rapidjson::Value& inObject
					  , const char* inPropertyName
					  , int value);

	// AddFloat()��,JSON��Document�ɁAfloat�^�̃f�[�^�����o��ǉ����܂��B
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON��Document����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 3�Ԗڂ̃p�����[�^�ɂ́A�v���p�e�B���𖽖����ē��́B
	// 4�Ԗڂ̃p�����[�^�ɂ́A���������v���p�e�B���܂�float�^��"�l"����́B
	// ����ɁA���͂����l��float�^�łȂ������ꍇ�A�x���𔭍s���܂��B
	static void AddFloat(rapidjson::Document::AllocatorType& alloc
						, rapidjson::Value& inObject
						, const char* inPropertyName
						, float value);


	// AddDouble()��,JSON��Document�ɁAfloat�^�̃f�[�^�����o��ǉ����܂��B
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON��Document����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 3�Ԗڂ̃p�����[�^�ɂ́A�v���p�e�B���𖽖����ē��́B
	// 4�Ԗڂ̃p�����[�^�ɂ́A���������v���p�e�B���܂�double�^��"�l"����́B
	// ����ɁA���͂����l��double�^�łȂ������ꍇ�A�x���𔭍s���܂��B
	static void AddDouble(rapidjson::Document::AllocatorType& alloc
						 , rapidjson::Value& inObject
						 , const char* inPropertyName
						 , double value);


	// AddString()��,JSON��Document�ɁAstring�^�̃f�[�^�����o��ǉ����܂��B
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON��Document����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 3�Ԗڂ̃p�����[�^�ɂ́A�v���p�e�B���𖽖����ē��́B
	// 4�Ԗڂ̃p�����[�^�ɂ́A���������v���p�e�B���܂�string�^��"�l"����́B
	// ����ɁA���͂����l��string�^�łȂ������ꍇ�A�x���𔭍s���܂��B
	static void AddString(rapidjson::Document::AllocatorType& alloc
						 , rapidjson::Value& inObject
						 , const char* inPropertyName
						 , const std::string& value);

	// AddBool()��,JSON��Document�ɁAbool�^�̃f�[�^�����o��ǉ����܂��B
	// 1�Ԗڂ̃p�����[�^�ɂ́AJSON��Document����́B
	// 2�Ԗڂ̃p�����[�^�ɂ́AJSON�I�u�W�F�N�g����́B
	// 3�Ԗڂ̃p�����[�^�ɂ́A�v���p�e�B���𖽖����ē��́B
	// 4�Ԗڂ̃p�����[�^�ɂ́A���������v���p�e�B���܂�bool�^��"�l"����́B
	// ����ɁA���͂����l��bool�^�łȂ������ꍇ�A�x���𔭍s���܂��B
	static void AddBool(rapidjson::Document::AllocatorType& alloc
					   , rapidjson::Value& inObject
					   , const char* inPropertyName
					   , bool value);

};

#endif //JSON_HELPER_H_
/*=============================================================================
/*		End of File
=============================================================================*/