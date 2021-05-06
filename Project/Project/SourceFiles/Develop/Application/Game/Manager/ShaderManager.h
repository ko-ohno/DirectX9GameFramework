/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ShaderManager.h] シェーダー管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：シェーダー管理クラス
=============================================================================*/
#ifndef SHADER_MANAGER_H_
#define	SHADER_MANAGER_H_ 

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"

/*-------------------------------------
/* シェーダーの型
-------------------------------------*/
enum class  ShaderType
{
	None = -1
	, Sprite			//スプライト
	, DissolveFade		//フェード
	, Billboard			//ビルボード
	, StandardMesh		//メッシュ(ボーンなし)
	, SkinMesh			//スキンメッシュ
	, ParticleEffect    //エフェクト
	, Gizmo				//ギズモ
	, Max
};

/*-------------------------------------
/* シェーダーの管理クラス
-------------------------------------*/
class ShaderManager
{
public:
	ShaderManager(class Game* game);
	~ ShaderManager(void);

	static ShaderManager* Create(class Game* game);

	bool StartUp(void);
	void Shutdown(void);
	
	class Game* GetGame(void) { return game_; }

	class Shader* ShaderDispatch(ShaderType shader);

private:
	bool Init(void);	//初期化
	void Uninit(void);	//終了化

	void LoadShaders(void);		//シェーダの読み込み
	void UnloadShaders(void);	//シェーダの破棄

private:
	//マネージャーの所有者
	class Game* game_;

	//シェーダーのリスト
	std::unordered_map<enum class ShaderType, class Shader*> unmap_shader_list_;
};

#endif //SHADER_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/