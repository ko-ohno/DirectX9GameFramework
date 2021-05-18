/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LightManager.h] ライト管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ライト管理クラス
=============================================================================*/
#ifndef LIGHT_MANAGER_H_
#define	LIGHT_MANAGER_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

enum class LightType
{
	None = -1
	, DirectionalLight
	, PointLight
	, SpotLight
	, Max
};

/*-------------------------------------
/* ライト管理クラス
-------------------------------------*/
class LightManager
{
public:
	LightManager(class Game* game);
	~LightManager(void);

	static LightManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止

private:
	bool Init(void);	 //初期化
	void Uninit(void);	 //終了化

public:
	//
	// メッシュの追加と削除
	//

	void AddLight(class Light* light);
	void RemoveLight(class Light* light);

	class Game* GetGame(void) { return game_; }

	std::vector<class Light*> GetLightList(void) { return light_list_; }
private:
	//マネージャーの所有者
	class Game* game_;

	//ライトのコンテナ
	std::vector<class Light*> light_list_;
};

#endif //LIGHT_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/