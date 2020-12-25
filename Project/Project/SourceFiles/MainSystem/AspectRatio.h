/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.h] �A�X�y�N�g�䗦�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�X�y�N�g�䗦�N���X
=============================================================================*/
#ifndef ASPECT_RATIO_H_
#define	ASPECT_RATIO_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �E�B���h�E�T�C�Y��ID
-------------------------------------*/
enum class window_size_id
{
	None = -1
	, SPLASH_SCREEN_500x600
	, _1280x_720
	, _1920x1080
	, FULL_SCREEN
	, MAX
};


/*-------------------------------------
/* �A�X�y�N�g�䗦�N���X
-------------------------------------*/
class AspectRatio
{
public:
	AspectRatio(void);
	~AspectRatio(void);

	class Vector2* CaiculationAspectRatio(const DWORD& dwWindowStyle);

private:
	class Vector2* GetFullScreenWindowSize(const DWORD& dwWindowStyle);
	

private:
	std::map<std::string, class Vector2*> aspect_ratio_list_;
};

static AspectRatio ar;


#endif //ASPECT_RATIO_H_
/*=============================================================================
/*		End of File
=============================================================================*/