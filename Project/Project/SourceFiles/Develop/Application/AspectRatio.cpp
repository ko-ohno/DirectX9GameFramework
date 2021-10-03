/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.cpp] �A�X�y�N�g�䗦�����v�Z�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�X�y�N�g�䗦�����v�Z�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "AspectRatio.h"
#include "Win32APIWindow.h"
#include "Math.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
AspectRatio::AspectRatio(void)
{	
	//������
	aspect_ratio_list_.clear();
	screen_scaler_.clear();

	//�A�X�y�N�g�䗦��16�F9�̔䗦�����{�ɂ������̒l
	//��):1920:1080��16�F9��120�{�ɂ����l

	//�g�嗦�̌v�Z
	//1920x1080��{��1.00�Ƃ��A�{��0.5���Œ�Ƃ��A�{��0.8���ő�(�t���X�N���[��������)�Ƃ���B
	const float maximize_scaler  = 0.85f;
	const float scaler_add_value = 0.05f;
	float scaler = 0.5f;
	for (;;)
	{
		screen_scaler_.push_back(scaler);
		scaler += scaler_add_value;
		if (scaler >= maximize_scaler) { break; }

		if (scaler >= maximize_scaler)
		{
			assert(!"�s���ȉ�ʔ䗦�̌v�Z�����Ă��܂��I�I");
		}
	}

	//��ʃT�C�Y�̍ő�l���擾
	Vector2 full_screen_window_size = Win32APIWindow().GetFullScreenSize();

	//��ʃT�C�Y�̃��X�g�̐���
	for (auto screen_scale : screen_scaler_)
	{
		//�v�Z��̃A�X�y�N�g�䗦���i�[
		const Vector2 calculated_aspect_ratio = full_screen_window_size * screen_scale;
	
		const std::string asepct_ratio_string = this->OutputAspectRatioString(calculated_aspect_ratio);

		//vector�z��Ɋi�[
		auto value = std::make_pair(asepct_ratio_string, Vector2(calculated_aspect_ratio));
		aspect_ratio_list_.push_back(value);

	}

	//�t���X�N���[���̏ꍇ�̕�����𐶐�
	const std::string full_asepct_ratio_string = this->OutputAspectRatioString(full_screen_window_size);

	//��ʃT�C�Y�̍ő�l��o�^
	auto value = std::make_pair("FullScreen("+ full_asepct_ratio_string +")"  ,  Vector2(full_screen_window_size));
	aspect_ratio_list_.push_back(value);
	screen_scaler_.push_back(1.f);		// �Ō�͌�����g�k�l�̔{����ۑ�
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
AspectRatio::~AspectRatio(void)
{
	while (!aspect_ratio_list_.empty())
	{
		aspect_ratio_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
AspectRatio* AspectRatio::Create(void)
{
	return NEW AspectRatio();
}

/*-----------------------------------------------------------------------------
/* �A�X�y�N�g�䗦�̃��X�g�擾�֐�
-----------------------------------------------------------------------------*/
std::vector<std::pair<std::string, class Vector2>> AspectRatio::GetAspectRatioList(void)
{
	return aspect_ratio_list_;
}

/*-----------------------------------------------------------------------------
/* �A�X�y�N�g�䗦�̊g�k�l
-----------------------------------------------------------------------------*/
std::vector<float> AspectRatio::GetScreenScalerList(void)
{
	return screen_scaler_;
}

/*-----------------------------------------------------------------------------
/* �A�X�y�N�g�䗦�̕����񐶐�
-----------------------------------------------------------------------------*/
std::string AspectRatio::OutputAspectRatioString(const Vector2& screenSize)
{
	//�A�X�y�N�g��̕\�L������̐���
	const std::string str_screen_width  = std::to_string(static_cast<int>(screenSize.x_));
	const std::string str_screen_height = std::to_string(static_cast<int>(screenSize.y_));

	//������̍���
	return std::string(str_screen_width + "x" + str_screen_height);
}

/*=============================================================================
/*		End of File
=============================================================================*/