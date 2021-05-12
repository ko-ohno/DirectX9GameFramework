/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.h] RapidJSON�T���v���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FJSON����T���v���[�N���X
=============================================================================*/
#ifndef JSON_SAMPLER_H_
#define	JSON_SAMPLER_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

//Qiita�L��
//https://qiita.com/k2ymg/items/eef3b15eaa27a89353ab

//RapidJSON�����h�L�������g
//https://rapidjson.org/index.html

//��L��URL��Qiita�̋L���ƌ����h�L�������g����ǂ��Ȃ������

/*-------------------------------------
/* RapidJSON�T���v���[�N���X
-------------------------------------*/
class JSONSampler
{
private:
	JSONSampler(void);

public:
	~JSONSampler(void);

	//�T���v���̌Ăяo��
	static void LoadSamples(void);

	//������f�[�^��DOM�ɓn���č\����́A�ǂݍ��ݕ\�����鏈��
	static void DOMParseSample01(void);
	static void DOMParseSample02(void);

	//����������̓��o�̓X�g���[��
	static void MemoryIOStreamingSample(void);

	//�t�@�C������̓��o�̓X�g���[��
	static void FileIOStreamingSample(void);

	//�\����̓G���[�R�[�h�̏o��
	static void ParseErrorSample(void);

	//Value�̌^���Ƃɍ\����͂���T���v��

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