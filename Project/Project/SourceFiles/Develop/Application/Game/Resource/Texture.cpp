/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Texture.cpp] テクスチャークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：テクスチャークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "Texture.h"
#include "../Manager/TextureManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
Texture::Texture(class TextureManager* manager, TextureType textureType)
	: texture_manager_(manager)
	, texture_type_id_(TextureType::None)
	, is_loading_complete_(false)
	, lpd3d_texture_(nullptr)
{
	//テクスチャIDの設定
	texture_type_id_ = textureType;

	//テクスチャーの読み込み
	is_loading_complete_ = this->LoadTexture(textureType);
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
Texture::~Texture()
{
	//テクスチャの解放
	SAFE_RELEASE_(lpd3d_texture_);
}

/*-----------------------------------------------------------------------------
/* テクスチャの読み込み処理
-----------------------------------------------------------------------------*/
bool Texture::LoadTexture(const TextureType textureType)
{
	auto lpd3d_device = *texture_manager_->GetGame()->GetGraphics()->GetLPD3DDevice();
	{
		auto texture_filepath = texture_manager_->GetTextureFilepathList().at(textureType);

		HRESULT hr = D3DXCreateTextureFromFile(lpd3d_device, texture_filepath.c_str(), &lpd3d_texture_);
		if (FAILED(hr))
		{
			assert(!"テクスチャーの作成に失敗しました！");
			return false;
		}

		hr = D3DXGetImageInfoFromFile(texture_filepath.c_str(), &d3dximage_info_);
		if (FAILED(hr))
		{
			assert(!"テクスチャーの画像情報の取得に失敗しました！");
			return false;
		}
	}
	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/