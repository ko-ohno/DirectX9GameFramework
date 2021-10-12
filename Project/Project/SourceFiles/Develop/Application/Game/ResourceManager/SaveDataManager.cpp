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

    while (!save_data_list_.empty())
    {
        delete save_data_list_.back();
        save_data_list_.pop_back();
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
        { static_cast<int>(ScoreRankLimits::S), ScoreRank::S },
        { static_cast<int>(ScoreRankLimits::A), ScoreRank::A },
        { static_cast<int>(ScoreRankLimits::B), ScoreRank::B },
        { static_cast<int>(ScoreRankLimits::C), ScoreRank::C },
        { static_cast<int>(ScoreRankLimits::D), ScoreRank::D }
    };

    // JSON�t�@�C���̏o��
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
                    // �X�R�A�̓���
                    JSONHelper::AddInt(doc.GetAllocator(), save_data, "score", init_save_data[i].GetScore());

                    // �X�R�A�����N�̓���
                    {
                        std::string score_rank;

                        switch (init_save_data[i].GetScoreRank())
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
    while (!save_data_list_.empty())
    {
        delete save_data_list_.back();
        save_data_list_.pop_back();
    }

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
                int       score_data       = save_data["score"].GetInt();
                char      score_rank_data  = save_data["score_rank"].GetString()[0];

                //�Z�[�u�f�[�^�ɃX�R�A�����N�̓��͂��s��
                ScoreRank input_score_rank = ScoreRank::None;
                {
                    switch (score_rank_data)
                    {
                    case 'S':
                        input_score_rank = ScoreRank::S;
                        break;

                    case 'A':
                        input_score_rank = ScoreRank::A;
                        break;

                    case 'B':
                        input_score_rank = ScoreRank::B;
                        break;

                    case 'C':
                        input_score_rank = ScoreRank::C;
                        break;

                    case 'D':
                        input_score_rank = ScoreRank::D;
                        break;

                    default:
                        std::string err_msg = "�Z�[�u�f�[�^�̃X�R�A�����N���ɁA�s���Ȓl���g�ݍ��܂�Ă��܂��B\n";
                        MessageBox(nullptr, err_msg.c_str(), "�x��", (MB_OK | MB_ICONWARNING));
                        break;
                    }
                }

                // �Z�[�u�f�[�^�����X�g�ɕۑ�
                this->AddSaveData(NEW SaveData(score_data, input_score_rank));
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
    // JSON�h�L�������g�I�u�W�F�N�g��Root��錾
    rapidjson::Document doc(rapidjson::kObjectType);
    {
        //Version�̋L�^
        const float version = data_version;
        {
            //�o�[�W�����̃f�[�^��擪�֓o�^
            JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);
        }

        //�Z�[�u�f�[�^�̃\�[�g
        this->SortBySaveData();

        // �Z�[�u�f�[�^�̍쐬
        int i = 0;
        for (auto save_data : save_data_list_)
        {
            i++;
            auto save_data_name = "save_data_" + std::to_string(i);

            // �Z�[�u�f�[�^�I�u�W�F�N�g�̃o�b�t�@�̍쐬
            rapidjson::Value save_data_object(rapidjson::kObjectType);
            {
                // �X�R�A�̓���
                JSONHelper::AddInt(doc.GetAllocator(), save_data_object, "score", save_data->GetScore());

                // �X�R�A�����N�̓���
                {
                    std::string score_rank;

                    switch (save_data->GetScoreRank())
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

                    JSONHelper::AddString(doc.GetAllocator(), save_data_object, "score_rank", score_rank);
                }

                // rapidjson�ł̃I�u�W�F�N�g���̐���
                rapidjson::Value rapidjson_object_data_name_;
                {
                    rapidjson_object_data_name_.SetString(save_data_name.c_str(), doc.GetAllocator());
                }

                //�Z�[�u�f�[�^�I�u�W�F�N�g�������o�Ƃ��Ēǉ�
                doc.AddMember(rapidjson_object_data_name_, save_data_object, doc.GetAllocator());
            }
        }
    }

    // �t�@�C���o��
    {
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
/* �X�R�A�����N�𕶎��֕ϊ����鏈��
-----------------------------------------------------------------------------*/
char SaveDataManager::ConvertToChar(ScoreRank scoreRank)
{
    char score_rank = '\0';

    switch (scoreRank)
    {
    case ScoreRank::S:
        score_rank = 'S';
        break;

    case ScoreRank::A:
        score_rank = 'A';
        break;

    case ScoreRank::B:
        score_rank = 'B';
        break;

    case ScoreRank::C:
        score_rank = 'C';
        break;

    case ScoreRank::D:
        score_rank = 'D';
        break;

    default:
        assert(!"SaveDataManager::ConvertToChar()�F�s���ȃX�R�A�����N���w�肳��Ă��܂��I");
        break;
    }

    return score_rank;
}

/*-----------------------------------------------------------------------------
/* �Z�[�u�f�[�^�̍쐬����
-----------------------------------------------------------------------------*/
void SaveDataManager::AddNewSaveData(SaveData* data)
{
    //�@�V�����f�[�^���H
    const bool is_new_date = data->IsGetNewData();
    if (is_new_date == false)
    {
        data->IsSetNewData(true);
    }

    // �X�R�A�����N�̃p�����[�^
    ScoreRank score_rank = ScoreRank::None;

    // �X�R�A�̎擾
    auto score = data->GetScore();

    // �X�R�A�̃����N�̐ݒ�
    {

        // �����N�̃X�R�A��������N
        int score_rank_limits[static_cast<int>(ScoreRankLimits::Max)] =
        {
            static_cast<int>(ScoreRankLimits::S),
            static_cast<int>(ScoreRankLimits::A),
            static_cast<int>(ScoreRankLimits::B),
            static_cast<int>(ScoreRankLimits::C),
            static_cast<int>(ScoreRankLimits::D)
        };

        // �X�R�A�����N�z��
        ScoreRank score_rank_list[static_cast<int>(ScoreRank::Max)] =
        {
            ScoreRank::S,
            ScoreRank::A,
            ScoreRank::B,
            ScoreRank::C,
            ScoreRank::D
        };

        // �X�R�A�̃����N���v�Z
        for (int i = 0; i < MAX_SAVE_DATA_COUNT; i++)
        {
            if (score >= static_cast<int>(score_rank_limits[i]))
            {
                score_rank = score_rank_list[i];
                break;
            }
        }
    }

    // �X�R�A�����N�̍X�V
    data->SetScoreRank(score_rank);

    // �Z�[�u�f�[�^�̒ǉ�����
    this->AddSaveData(data);
}

/*-----------------------------------------------------------------------------
/* �Z�[�u�f�[�^�̒ǉ�����
-----------------------------------------------------------------------------*/
void SaveDataManager::AddSaveData(SaveData* data)
{
    //�`��D�揇��
    int	score = data->GetScore();

    //�}���ł���܂ŃR���|�[�l���g�̌���
    auto iter = save_data_list_.begin();
    for (;
        iter != save_data_list_.end();
        ++iter)
    {
        //�@�X�R�A���傫��������
        if (score > (*iter)->GetScore())
        {
            break;
        }

        // �X�R�A��������������
        if (score == (*iter)->GetScore())
        {
            break;
        }
    }

    //�f�[�^�̑}��
    save_data_list_.insert(iter, data);	
}

/*-----------------------------------------------------------------------------
/* �Z�[�u�f�[�^�̍폜����
-----------------------------------------------------------------------------*/
void SaveDataManager::RemoveSaveData(SaveData* data)
{
    auto iter = std::find(save_data_list_.begin()	//�͈�0�`
                         , save_data_list_.end()	//�͈͍ő�܂�
                         , data);			        //�T���Ώ�

    if (iter != save_data_list_.end())
    {
        save_data_list_.erase(iter);
    }
}

/*-----------------------------------------------------------------------------
/* JSON�t�@�C���ւ̃Z�[�u����
-----------------------------------------------------------------------------*/
void SaveDataManager::SortBySaveData(void)
{
    std::stable_sort(
        save_data_list_.begin()
        , save_data_list_.end()
        , [](const SaveData* left, const SaveData* right)
        {
            if (left->GetScore() == right->GetScore())
            {

                return left->GetScore() < right->GetScore();
            }
            else
            {
                return left->GetScore() > right->GetScore();
            }
        }
    );
}

/*=============================================================================
/*		End of File
=============================================================================*/