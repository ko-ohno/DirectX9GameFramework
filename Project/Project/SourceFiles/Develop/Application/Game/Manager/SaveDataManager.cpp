/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SaveDataManager.cpp] �Z�[�u�f�[�^�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Z�[�u�f�[�^�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "SaveDataManager.h"

//RapidJSON�̗��p
#include "JSONManager/JSONManager.h"
#include "JSONManager/JSONHelper.h"

static constexpr float data_version = 1.00f;

#pragma warning(disable:4996)

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
SaveDataManager::SaveDataManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
SaveDataManager::~SaveDataManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
SaveDataManager* SaveDataManager::Create(Game* game)
{
	return NEW SaveDataManager(game);
}

/*-----------------------------------------------------------------------------
/* �N������
-----------------------------------------------------------------------------*/
bool SaveDataManager::StartUp(void)
{
	//���g�̏�����
	const bool collider_manager_init = this->Init();
	if (collider_manager_init == false)
	{
		assert(!"SaveDataManager::StartUp()�F�Z�[�u�f�[�^�}�l�[�W���̏������Ɏ��s���܂����B");
		return false;
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* ��~����
-----------------------------------------------------------------------------*/
void SaveDataManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool SaveDataManager::Init(void)
{
    // �t�@�C���p�X�̏ꏊ��������
    data_file_root_path_ = "Assets/SaveData/";

    // �t�@�C�����̐ݒ�
    data_file_name_ = "SaveData.json";

    // �t���p�X�̍쐬
    auto file_path = data_file_root_path_ + data_file_name_;

	// �Z�[�u�f�[�^�̓ǂݍ���
	{
        const bool is_load_failed = this->LoadJSON(file_path);
        if (is_load_failed == false)
        {
            std::string err_msg = "SaveDataManager::Init()�F�Z�[�u�f�[�^�̓ǂݍ��݂Ɏ��s���܂���";
            MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));
            return false;
        }
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void SaveDataManager::Uninit(void)
{
    // �t���p�X�̍쐬
    auto file_path = data_file_root_path_ + data_file_name_;

    // �Z�[�u�f�[�^�̍쐬
    {
        this->SaveJSON(file_path);
    }
}

/*-----------------------------------------------------------------------------
/* JSON�̃f�[�^�t�@�C���̐V�K�쐬����
-----------------------------------------------------------------------------*/
void SaveDataManager::CreateNewJSONDataFile(const std::string& inFileName)
{
    // �Z�[�u�f�[�^�̏������f�[�^
    SaveData init_save_data[MAX_SAVE_DATA_COUNT] = 
    {
        { 1, 4000, ScoreRank::S},
        { 2, 3000, ScoreRank::A},
        { 3, 2000, ScoreRank::B},
        { 4, 1000, ScoreRank::C},
        { 5,  500, ScoreRank::D}
    };

    //JSON�t�@�C���̏o��
    {
        // JSON�h�L�������g��Root��錾
        rapidjson::Document doc(rapidjson::kObjectType);
        {
            //Version�̋L�^
            const float version = data_version;
            {
                //�o�[�W�����̃f�[�^��擪�֓o�^
                JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);
            }

            // �Z�[�u�f�[�^�̍쐬
            for (int i = 0; i < MAX_SAVE_DATA_COUNT; i++)
            {
                auto save_data_name = "save_data_" + std::to_string(i+1);

                // �Z�[�u�f�[�^�I�u�W�F�N�g�̃o�b�t�@�̍쐬
                rapidjson::Value save_data(rapidjson::kObjectType);
                {     
                    // �����L���O�̓���
                    JSONHelper::AddInt(doc.GetAllocator(), save_data, "ranking", init_save_data[i].ranking_);

                    // �X�R�A�̓���
                    JSONHelper::AddInt(doc.GetAllocator(), save_data, "score", init_save_data[i].score_);

                    // �X�R�A�����N�̓���
                    {
                        std::string score_rank;

                        switch (init_save_data[i].score_rank_)
                        {
                        case ScoreRank::S:
                            score_rank = "S";
                            break;

                        case ScoreRank::A:
                            score_rank = "A";
                            break;

                        case ScoreRank::B:
                            score_rank = "B";
                            break;

                        case ScoreRank::C:
                            score_rank = "C";
                            break;

                        case ScoreRank::D:
                            score_rank = "D";
                            break;

                        default:
                            assert(!"SaveDataManager::CreateNewJSONDataFile()�F�s���ȃX�R�A�����N���w�肳��Ă��܂��I");
                            break;
                        }

                        JSONHelper::AddString(doc.GetAllocator(), save_data, "score_rank", score_rank);
                    }

                    // rapidjson�ł̃I�u�W�F�N�g���̐���
                    rapidjson::Value rapidjson_object_data_name_;
                    {
                        rapidjson_object_data_name_.SetString(save_data_name.c_str(), doc.GetAllocator());
                    }

                    //�Z�[�u�f�[�^�I�u�W�F�N�g�������o�Ƃ��Ēǉ�
                    doc.AddMember(rapidjson_object_data_name_, save_data, doc.GetAllocator());
                }
            }
        }

        // JSON�p�̕�����o�b�t�@���쐬
        rapidjson::StringBuffer buffer;

        // �����ȕ�����o�b�t�@�̃A�h���X��o�^�B������o�b�t�@���C���f���g���ꂽ��Ԃ֕ϊ��ł���悤��
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

        // �h�L�������g�̕�����o�b�t�@���\����́BPrettyWriter�ɂ���ăC���f���g���ꂽ��ԂցB
        doc.Accept(writer);

        // �ϊ����ꂽ������o�b�t�@����f�[�^���擾
        const char* output = buffer.GetString();

        // JSON�t�@�C���Ƃ��ďo��
        std::ofstream outFile(inFileName);
        if (outFile.is_open())
        {
            outFile << output;
        }
    }
}

/*-----------------------------------------------------------------------------
/* JSON�̓ǂݍ��ݏ���
-----------------------------------------------------------------------------*/
bool SaveDataManager::LoadJSON(const std::string& inFileName)
{
    // �Z�[�u�f�[�^�̃��X�g���N���A
    save_data_list_.clear();

    //JSON�h�L�������g�I�u�W�F�N�g��Root�𐶐�
    rapidjson::Document doc(rapidjson::kObjectType);

    //JSON�t�@�C���̓ǂݍ���
    {
        const bool is_file_load_failed = JSONManager::LoadJSON(inFileName, doc);
        if (is_file_load_failed == false)
        {
            std::string err_msg = "�Z�[�u�f�[�^�̃t�@�C���ǂݍ��݂Ɏ��s���܂����B\n";
            err_msg = err_msg + "�Z�[�u�f�[�^�p�̃t�@�C����V�K�쐬���܂��B\n";
            MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));

            //�Z�[�u�f�[�^�t�@�C���̐V�K�쐬
            {
                this->CreateNewJSONDataFile(inFileName);              
            }
            // �쐬���ꂽJSON�t�@�C���̓ǂݍ���
            JSONManager::LoadJSON(inFileName, doc);
        }

        // �f�[�^�̓ǂݍ���
        {
            //�@�o�[�W�����̓ǂݍ���
            float version = 0.f;
            if (!JSONHelper::GetFloat(doc, "version", version)
                || version != data_version)
            {
                std::string err_msg = "�Z�[�u�f�[�^��version���Ⴂ�܂����A���̂܂܃V�X�e�������s���܂��B\n";
                MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));
            }

            //�@�Z�[�u�f�[�^�̍ő吔�܂œǂݍ���
            for (int i = 0; i < MAX_SAVE_DATA_COUNT; i++)
            {
                std::string save_data_name = "save_data_" + std::to_string(i+1);

                // �Z�[�u�f�[�^�I�u�W�F�N�g�̓ǂݍ���
                const rapidjson::Value& save_data = doc[save_data_name.c_str()];
                if (save_data.IsObject() == false)
                {
                    std::string err_msg = "�Z�[�u�f�[�^�̏�񂪓ǂݍ��߂܂���ł����B\n";
                    err_msg = err_msg + "�Z�[�u�f�[�^(" + std::to_string(i + 1) + ")�F�ǂݍ��݂Ɏ��s�B";
                    MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));
                    return false;
                }

                // �Z�[�u�f�[�^�擾�p�o�b�t�@
                SaveData save_data_buffer;

                // �����L���O�̓ǂݍ���
                save_data_buffer.ranking_ = save_data["ranking"].GetInt();

                // �X�R�A�̓ǂݍ���
                save_data_buffer.score_ = save_data["score"].GetInt();

                // �X�R�A�����N�̓ǂݍ���
                std::string score_rank = save_data["score_rank"].GetString();

                // �����𐔒l�֕ϊ��BScoreRank�ƈ�v���镶����K�p
                save_data_buffer.score_rank_ = static_cast<ScoreRank>(score_rank.at(0));

                //�Z�[�u�f�[�^�ɃG���[���܂܂�Ă��邩
                bool is_error = false;
                {
                    switch (save_data_buffer.score_rank_)
                    {
                    case ScoreRank::None:
                        is_error = true;
                        break;

                    case ScoreRank::S:
                        break;

                    case ScoreRank::A:
                        break;

                    case ScoreRank::B:
                        break;

                    case ScoreRank::C:
                        break;

                    case ScoreRank::D:
                        break;

                    case ScoreRank::Max:
                        is_error = true;
                        break;

                    default:
                        is_error = true;
                        break;
                    }

                    if (is_error)
                    {
                        std::string err_msg = "�Z�[�u�f�[�^�̃X�R�A�����N���ɁA�s���Ȓl���g�ݍ��܂�Ă��܂��B\n";
                        MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));
                    }
                }

                // �Z�[�u�f�[�^�����X�g�ɕۑ�
                save_data_list_.emplace_back(save_data_buffer);
            }
        }
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* JSON�t�@�C���ւ̃Z�[�u����
-----------------------------------------------------------------------------*/
void SaveDataManager::SaveJSON(const std::string& inFileName)
{
    //// JSON�h�L�������g��Root��錾
    //rapidjson::Document doc(rapidjson::kObjectType);
    //{
    //    //Version�̋L�^
    //    const float version = data_version;
    //    {
    //        //�o�[�W�����̃f�[�^��擪�֓o�^
    //        JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);
    //    }

    //    //�v���p�e�B�I�u�W�F�N�g�̃o�b�t�@�̍쐬
    //    rapidjson::Value property(rapidjson::kObjectType);
    //    {
    //        //�v���p�e�B�I�u�W�F�N�g�̐���
    //        this->SaveProperties(doc.GetAllocator(), property);

    //        //�v���p�e�B�I�u�W�F�N�g�������o�Ƃ��Ēǉ�
    //        doc.AddMember("Properties", property, doc.GetAllocator());
    //    }
    //}

    //// JSON�p�̕�����o�b�t�@���쐬
    //rapidjson::StringBuffer buffer;

    //// �����ȕ�����o�b�t�@�̃A�h���X��o�^�B������o�b�t�@���C���f���g���ꂽ��Ԃ֕ϊ��ł���悤��
    //rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    //// �h�L�������g�̕�����o�b�t�@���\����́BPrettyWriter�ɂ���ăC���f���g���ꂽ��ԂցB
    //doc.Accept(writer);

    //// �ϊ����ꂽ������o�b�t�@����f�[�^���擾
    //const char* output = buffer.GetString();

    //// JSON�t�@�C���Ƃ��ďo��
    //std::ofstream outFile(inFileName);
    //if (outFile.is_open())
    //{
    //    outFile << output;
    //}
}

/*=============================================================================
/*		End of File
=============================================================================*/