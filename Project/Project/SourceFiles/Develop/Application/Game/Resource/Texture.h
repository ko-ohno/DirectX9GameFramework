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
	Texture(TextureManager* manager, TextureType textureType);
	Texture(const LPDIRECT3DTEXTURE9& texture);
	~Texture(void);

	//テクスチャの読み込み
	bool LoadTexture(const TextureType textureType);
	
	//テクスチャの読み込みができているか
	bool IsLoadCompleted(void) { return is_loading_complete_; }

	//
	// テクスチャのデータ取得関数
	//

	TextureType			GetTextureTypeID(void) { return texture_type_id_; }

	LPDIRECT3DTEXTURE9	GetTexture(void) { return lpd3d_texture_; }

	D3DXIMAGE_INFO*		GetTextureImageInfo(void) { return &d3dximage_info_; }

private:
	// テクスチャーの所有者
	class TextureManager* texture_manager_;

	//
	// テクスチャーのデータ
	//

	bool				is_loading_complete_;

	TextureType			texture_type_id_;
	LPDIRECT3DTEXTURE9	lpd3d_texture_;

	//テクスチャの画像サイズ等の情報
	D3DXIMAGE_INFO		d3dximage_info_;
};

#endif //TEXTURE_H_
/*=============================================================================
/*		End of File
=============================================================================*/