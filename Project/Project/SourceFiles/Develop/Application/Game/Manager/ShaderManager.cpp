/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ShaderManager.cpp] シェーダー管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：シェーダー管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../StdAfx.h"
#include "ShaderManager.h"
#include "../Game.h"

#include "../Shader/SpriteShader.h"
#include "../Shader/DissolveShader.h"

#include "../Shader/BillboardShader.h"

#include "../Shader/StdMeshShader.h"
#include "../Shader/SkinMeshShader.h"


/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
ShaderManager::ShaderManager(Game* game)
	: game_(game)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
ShaderManager::~ShaderManager(void)
{
}

/*-----------------------------------------------------------------------------
/* ファクトリメソッド
-----------------------------------------------------------------------------*/
ShaderManager* ShaderManager::Create(Game* game)
{
	return NEW ShaderManager(game);
}

/*-----------------------------------------------------------------------------
/* シェーダーマネージャーの起動
-----------------------------------------------------------------------------*/
bool ShaderManager::StartUp(void)
{
	//マネージャの初期化
	const bool shader_manager_init = this->Init();
	if(shader_manager_init == false)
	{
		assert(!"ShaderManager::StartUp()：シェーダーマネージャの初期化に失敗しました。");
		return false;
	}

	//シェーダのリストの作成
	this->LoadShaders();

	return true;
}

/*-----------------------------------------------------------------------------
/* シェーダーマネージャーの停止
-----------------------------------------------------------------------------*/
void ShaderManager::Shutdown(void)
{
	//シェーダーの破棄
	this->UnloadShaders();

	//マネージャーの終了
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool ShaderManager::Init(void)
{
	//シェーダーのリストの初期化
	unmap_shader_list_.clear(); 

	if (!unmap_shader_list_.empty())
	{
		return false;
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ShaderManager::Uninit(void)
{
	//シェーダーのリストの破棄
	unmap_shader_list_.clear();
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void ShaderManager::LoadShaders(void)
{	
	//シェーダー
	unmap_shader_list_[ShaderType::Sprite]			= NEW SpriteShader(this);
	unmap_shader_list_[ShaderType::DissolveFade]	= NEW DissolveFadeShader(this);
	unmap_shader_list_[ShaderType::Billboard]		= NEW BillboardShader(this);
	unmap_shader_list_[ShaderType::StandardMesh]	= NEW StdMeshShader(this);
	unmap_shader_list_[ShaderType::SkinMesh]		= NEW SkinMeshShader(this);
	unmap_shader_list_[ShaderType::ParticleEffect]  = nullptr; //Effecseerの描画ライブラリ使用のため
}

/*-----------------------------------------------------------------------------
/* シェーダの破棄
-----------------------------------------------------------------------------*/
void ShaderManager::UnloadShaders(void)
{
	for (auto shader : unmap_shader_list_)
	{
		delete shader.second;
		shader.second = nullptr;
	}
}

/*-----------------------------------------------------------------------------
/* シェーダの切り替え
-----------------------------------------------------------------------------*/
Shader* ShaderManager::ShaderDispatch(ShaderType shaderTypeID)
{
	const bool shader_error = (shaderTypeID <= ShaderType::None
							  || shaderTypeID >= ShaderType::Max);
	if (shader_error)
	{
		assert(!"不正なシェーダーの設定が割り当てられようとしています。");
	}

	return unmap_shader_list_.at(shaderTypeID);
}

/*=============================================================================
/*		End of File
=============================================================================*/