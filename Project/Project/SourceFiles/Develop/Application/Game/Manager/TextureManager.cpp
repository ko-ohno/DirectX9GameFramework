/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TextureManager.cpp] テクスチャー管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：テクスチャー管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "TextureManager.h"
#include "../Resource/Texture.h"

//テクスチャーのリスト
const char* TextureManager::TextureTypeNames[static_cast<int>(TextureType::Max)] = {
	//自分自身
	"Sample"
	, "Prototype"
	, "Planet"
};

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
TextureManager::TextureManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
TextureManager::~TextureManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
TextureManager* TextureManager::Create(Game* game)
{
	return NEW TextureManager(game);
}

/*-----------------------------------------------------------------------------
/* 起動処理
-----------------------------------------------------------------------------*/
bool TextureManager::StartUp(void)
{
	//自身の初期化
	const bool texture_manager_init =  this->Init();
	if (texture_manager_init == false)
	{
		assert(!"TextureManager::StartUp()：テクスチャーマネージャの初期化に失敗しました。");
		return false;
	}

	//テクスチャーの読み込み
	{
		//this->LoadTexture(TextureType::Sample);
		//this->LoadTexture(TextureType::Prototype);
		//this->LoadTexture(TextureType::Planet);
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 停止処理
-----------------------------------------------------------------------------*/
void TextureManager::Shutdown(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool TextureManager::Init(void)
{
	// テクスチャのルートパスを設定
	texture_root_path_ = "Assets/Textures/";

	// リストの初期化
	unmap_texture_path_list_.clear();
	{
		unmap_texture_path_list_[TextureType::Sample]    = "tex1.bmp";
		unmap_texture_path_list_[TextureType::Prototype] = "PrototypingTextures/texture_01.png";
		unmap_texture_path_list_[TextureType::Planet]	 = "Planet.png";

	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void TextureManager::Uninit(void)
{
	while (!texture_list_.empty())
	{
		delete texture_list_.back();
		texture_list_.pop_back();
	}
}

/*-----------------------------------------------------------------------------
/* テクスチャの読み込み処理
-----------------------------------------------------------------------------*/
Texture* TextureManager::LoadTexture(TextureType textureTypeID)
{
	//テクスチャがあったら
	auto texture = this->FindTexture(textureTypeID);
	if (texture != nullptr)
	{
		return texture;
	}
	else
	{
		//テクスチャがなかったら
		const bool is_texture_list_out_of_range = ((textureTypeID == TextureType::None)
											      || (textureTypeID == TextureType::Max));
		if (is_texture_list_out_of_range)
		{
			assert(!"範囲外のテクスチャIDを参照しようとしています！");
			return nullptr;
		}
		this->AddTexture(NEW Texture(this, textureTypeID));
	}
	return this->FindTexture(textureTypeID);
}

/*-----------------------------------------------------------------------------
/* テクスチャの解放処理
-----------------------------------------------------------------------------*/
void TextureManager::ReleaseTexture(TextureType textureTypeID)
{
	for (auto texture : texture_list_)
	{
		auto id = texture->GetTextureTypeID();

		if (id == textureTypeID)
		{
			delete texture;
		}
	}
}

/*-----------------------------------------------------------------------------
/* テクスチャ検索処理
-----------------------------------------------------------------------------*/
Texture* TextureManager::FindTexture(TextureType textureTypeID)
{
	//テクスチャリストの検索
	for (auto texture : texture_list_)
	{
		//現在の調査対象からIDを取得
		auto id = texture->GetTextureTypeID();

		//取得したIDとtextureType
		if (id == textureTypeID)
		{
			return texture;
		}
	}
	return nullptr;
}

/*-----------------------------------------------------------------------------
/* テクスチャの追加処理
-----------------------------------------------------------------------------*/
void TextureManager::AddTexture(Texture* texture)
{
	texture_list_.emplace_back(texture);
}

/*-----------------------------------------------------------------------------
/* テクスチャの削除処理
-----------------------------------------------------------------------------*/
void TextureManager::RemoveTexture(Texture* texture)
{
	auto iter = std::find(texture_list_.begin() //範囲0～
						 , texture_list_.end()	//範囲最大まで
						 , texture);			//探す対象

	if (iter != texture_list_.end())
	{
		texture_list_.erase(iter);
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/