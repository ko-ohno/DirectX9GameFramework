/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.h] アスペクト比率クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アスペクト比率クラス
=============================================================================*/
#ifndef ASPECT_RATIO_H_
#define	ASPECT_RATIO_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* ウィンドウサイズのID
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
/* アスペクト比率クラス
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