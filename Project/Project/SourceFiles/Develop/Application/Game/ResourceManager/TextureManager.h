/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TextureManager.h] テクスチャー管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：テクスチャー管理クラス
=============================================================================*/
#ifndef TEXTURE_MANAGER_H_
#define	TEXTURE_MANAGER_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* テクスチャの種類
-------------------------------------*/
enum class TextureType
{
	None = -1
	, Sample
	, Prototype
	, Blank
	, FarReticle
	, NearReticle
	, Planet
	, Max
};


/*-------------------------------------
/* テクスチャー管理クラス
-------------------------------------*/
class TextureManager
{
public:
	static const char* TextureTypeNames[static_cast<int>(TextureType::Max)];

public:
	TextureManager(class Game* game);
	~TextureManager(void);

	static TextureManager* Create(class Game* game);

	bool StartUp(void);	 //起動
	void Shutdown(void); //停止

private:

	bool Init(void);	//初期化
	void Uninit(void);	//終了化

public:
	//テクスチャのルートパスの取得
	std::string GetTextureRootpath(void) const { return texture_root_path_; }

	//テクスチャの読み込み
	class Texture* LoadTexture(TextureType textureTypeID);

	//テクスチャの解放
	void ReleaseTexture(TextureType textureTypeID);

	//テクスチャを検索する
	class Texture* FindTexture(TextureType textureTypeID);

	//
	// テクスチャの追加と削除
	//

	void AddTexture(class Texture* texture);
	void RemoveTexture(class Texture* texture);

	std::unordered_map<TextureType, std::string> GetTextureFilepathList(void) { return unmap_texture_path_list_; }

	class Game* GetGame(void) { return game_; }
	 
private:
	//マネージャの所有者
	class Game* game_;

	//テクスチャのルートパス
	std::string texture_root_path_;

	//テクスチャーのパスリスト
	std::unordered_map<TextureType, std::string> unmap_texture_path_list_;

	//テクスチャーのコンテナ
	std::vector<class Texture*> texture_list_;
};

#endif //TEXTURE_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/