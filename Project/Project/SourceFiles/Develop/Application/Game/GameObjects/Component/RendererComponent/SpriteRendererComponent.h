/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteRendererComponent.h] スプライトレンダラーコンポーネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトレンダラーコンポーネントクラス
=============================================================================*/
#ifndef SPRITE_RENDERER_H_
#define	SPRITE_RENDERER_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* スプライトシェーダクラス
-------------------------------------*/
class SpriteRendererComponent : public RendererComponent
{
public:
	SpriteRendererComponent(class GameObject* owner, int drawOrder = 200);
	~SpriteRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::SpriteRendererComponent; };

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
		texture_cut_width_  = textureCutWidth;
		texture_cut_height_ = textureCutHeight;
	}

	//テクスチャの設定
	void			SetTexture(TextureType textureTypeID);

	//テクスチャの取得
	class Texture*	GetTexture();

	//テクスチャ情報の取得
	D3DXIMAGE_INFO*	GetTextureImageInfo();

public:

	//描画座標をポリゴンの中央へ
	inline void IsSetDrawingPositionToCenter(const bool isOffsetScaleingCenter) { is_offset_scale_ = isOffsetScaleingCenter; }

	//回転成分の操作

	inline void SetRotate(float degree)
	{
		//回転情報の有効化
		is_affine_ = true;

		//回転
		radian_	   = Math::ToRadian(degree);
	}

	inline void AddRotate(float addValueDegree)
	{
		//回転情報の有効化
		is_affine_  = true;

		//回転
		radian_    += Math::ToRadian(addValueDegree);
	}

	inline float GetRadian(void) const { return radian_; }
	inline float GetDegree(void) const { return degree_; }

private:
	//全スプライト共通の頂点用のデータ

	static constexpr int			MAX_VERTEX_COUNT = 4;	//頂点バッファ数
	static LPDIRECT3DVERTEXBUFFER9	vertex_buffer_;			//頂点バッファ

	static constexpr int			MAX_INDEX_COUNT = 6;	//インデックスバッファ
	static LPDIRECT3DINDEXBUFFER9	index_buffer_;			//インデックスバッファ数

	static VERTEX_STD*				vertex_buffer_address_;	//頂点バッファのアドレス
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

	//中央座標にオフセットするか
	bool is_offset_scale_;

	//頂点座標をアフィン変換するか
	bool is_affine_;

	//座標
	//親クラスRendererComponenで定義ずみ

	//ポリゴンのサイズ
	//親クラスRendererComponenで定義ずみ

	//回転角度
	float degree_;
	float radian_;
};

#endif //SPRITE_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/