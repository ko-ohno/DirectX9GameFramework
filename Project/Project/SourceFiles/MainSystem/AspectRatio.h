/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.h] �A�X�y�N�g�䗦�����v�Z�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�X�y�N�g�䗦�����v�Z�N���X
=============================================================================*/
#ifndef ASPECT_RATIO_H_
#define	ASPECT_RATIO_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �A�X�y�N�g�䗦�����v�Z�N���X
-------------------------------------*/
class AspectRatio
{
public:
	AspectRatio(void);
	~AspectRatio(void);

	static AspectRatio* Create(void);

	std::vector<std::pair<std::string, class Vector2>> GetAspectRatioList(void);
	std::vector<float> GetScreenScalerList(void);

private:
	std::string OutputAspectRatioString(const class Vector2& screenSize);

private:
	std::vector<std::pair<std::string, class Vector2>> aspect_ratio_list_;
	std::vector<float> screen_scaler_;
};

#endif //ASPECT_RATIO_H_
/*=============================================================================
/*		End of File
=============================================================================*/