/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Texture.h] テクスチャークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：テクスチャークラス
=============================================================================*/
#ifndef TEXTURE_H_
#define	TEXTURE_H_

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "../Manager/TextureManager.h"


/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* テクスチャークラス
-------------------------------------*/
class Texture
{
public:
	Texture(class TextureManager* manager, TextureType textureType);
	~Texture(void);

	//テクスチャの読み込み
	bool LoadTexture(const TextureType textureType);
	
	bool IsLoadCompleted(void) { return is_loading_complete_; }

	TextureType GetTextureTypeID(void) { return texture_type_id_; }

	LPDIRECT3DTEXTURE9 GetTexture(void) { return lpd3d_texture_; }

	D3DXIMAGE_INFO* GetTextureImageInfo(void) { return &d3dximage_info_; }

private:
	//テクスチャーの所有者
	class TextureManager* texture_manager_;

	//ロードできたか
	bool is_loading_complete_;

	//テクスチャーのID
	enum class TextureType texture_type_id_;

	//テクスチャの画像データ
	LPDIRECT3DTEXTURE9 lpd3d_texture_;

	//テクスチャのサイズ等の情報
	D3DXIMAGE_INFO	   d3dximage_info_;
};

#endif //TEXTURE_H_
/*=============================================================================
/*		End of File
=============================================================================*/