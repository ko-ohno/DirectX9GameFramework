/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[AspectRatio.h] アスペクト比率自動計算クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：アスペクト比率自動計算クラス
=============================================================================*/
#ifndef ASPECT_RATIO_H_
#define	ASPECT_RATIO_H_

/*--- インクルードファイル ---*/
#include "../StdAfx.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* アスペクト比率自動計算クラス
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