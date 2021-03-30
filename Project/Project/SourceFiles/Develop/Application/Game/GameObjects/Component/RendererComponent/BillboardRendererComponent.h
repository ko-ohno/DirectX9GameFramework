/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BillboardRendererComponent.h] モジュールヘッダ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：
=============================================================================*/
#ifndef BILLBOARD_RENDERER_H_
#define	BILLBOARD_RENDERER_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* クラス
-------------------------------------*/
class BillboardRendererComponent : public RendererComponent
{
public:
	BillboardRendererComponent(class GameObject* owner, int drawOrder = 100);
	~BillboardRendererComponent(void);

	bool Init(void);
	void Uninit(void);

	void Draw(class Shader* shader, class Camera* camera) override;

private:
	//頂点用バッファ作成関数群

	bool CreateVertexBuffer(void);
	bool CreateIndexBuffer(void);

	void ComputeVertexBuffer(void);

public:

	//UV座標の計算
	void SetUVAnimation(int textureCutX = 0, int textureCutY = 0, int textureCutWidth = 0, int textureCutHeight = 0)
	{
		//UV座標を計算するかのフラグ
		is_compute_texcord_ = true;

		//UV座標の計算
		texture_cut_x_ = textureCutX;
		texture_cut_y_ = textureCutY;
		texture_cut_width_ = textureCutWidth;
		texture_cut_height_ = textureCutHeight;
	}

	//テクスチャの設定
	void			SetTexture(TextureType textureTypeID);

	//テクスチャの取得
	class Texture*	GetTexture(void);

	//テクスチャ情報の取得
	D3DXIMAGE_INFO* GetTextureImageInfo(void);

public:
	//回転成分の操作

	inline void SetRotate(float degree) { radian_ = Math::ToRadian(degree); }

	inline void AddRotate(float addValueDegree) { radian_ += Math::ToRadian(addValueDegree); }

	inline float GetRadian(void) const { return radian_; }
	inline float GetDegree(void) const { return degree_; }

private:
	//全ビルボード共通の頂点用のデータ

	static constexpr int			MAX_VERTEX_COUNT = 4;	//頂点バッファ数
	static LPDIRECT3DVERTEXBUFFER9	vertex_buffer_;			//頂点バッファ

	static constexpr int			MAX_INDEX_COUNT = 6;	//インデックスバッファ
	static LPDIRECT3DINDEXBUFFER9	index_buffer_;			//インデックスバッファ数

	static VERTEX_MESH*				vertex_buffer_address_;	//頂点バッファのアドレス
	static LPWORD*					index_buffer_address_;	//インデックスバッファのアドレス

	//UV座標計算をするか？
	bool is_compute_texcord_;

	//UV座標の計算用

	int texture_cut_x_;
	int texture_cut_y_;
	int texture_cut_width_;
	int texture_cut_height_;

private:

	//テクスチャデータ
	class Texture* texture_;

private:
	//
	// 姿勢制御用のデータ
	//

	//回転行列
	//親クラスRendererComponenで定義ずみ

	//ワールド行列
	//親クラスRendererComponenで定義ずみ

	//座標
	//親クラスRendererComponenで定義ずみ

	//ポリゴンのサイズ
	//親クラスRendererComponenで定義ずみ

	//回転角度
	float degree_;
	float radian_;

private:
	//プロジェクション行列
	D3DXMATRIX projection_matrix_;
};

#endif //BILLBOARD_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/