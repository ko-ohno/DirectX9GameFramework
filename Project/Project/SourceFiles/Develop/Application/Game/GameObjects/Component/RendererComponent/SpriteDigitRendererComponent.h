/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteDigitRendererComponent.h] スプライトの桁数描画コンポーネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトの桁数描画コンポーネントクラス
=============================================================================*/
#ifndef SPRITE_DIGIT_RENDERER_H_
#define	SPRITE_DIGIT_RENDERER_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"


/*-------------------------------------
/* スプライトの桁数描画コンポーネント
-------------------------------------*/
class SpriteDigitRendererComponent : public RendererComponent
{
public:
	SpriteDigitRendererComponent(class GameObject* owner, int drawOrder = 200);
	~SpriteDigitRendererComponent(void);
	
private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::SpriteDigitRendererComponent; };

	// テクスチャを設定する
	void SetTexture(TextureType textureType) { texture_type_ = textureType; };

	// 桁の描画座標をポリゴンの中心にするか
	void IsSetDrawingPositionToCenter(bool isIDrawingPositionToCenter) { is_drawing_position_to_center_ = isIDrawingPositionToCenter; }

	// テクスチャの設定　
	void IsSetFontTextureUVOriginZero(bool isTextureUVOriginZero) { is_font_texture_uv_origin_zero_ = isTextureUVOriginZero; }

	// 色情報の設定
	void SetVertexColor(int red = 255, int green = 255, int blue = 255, int alpha = 255)
	{
		red_	= red;
		green_	= green;
		blue_	= blue;
		alpha_  = alpha;
	}

	// 描画する有効桁数の設定
	void SetDrawableDigitLength(int drawableDigitLength) { drawable_digit_length_ = (drawableDigitLength -1); };

	// フォントの幅を設定
	int GetFontWidth(void) { return font_width_; }
	void SetFontWidth(int width) { font_width_ = width; }

	// フォントの高さを設定
	int GetFontHeight(void) { return font_height_; }
	void SetFontHeight(int height) { font_height_ = height; }

	// 整数データの設定
	void SetIntData(int data) { int_data_ = data; }

	// 桁の間のオフセット値を設定する
	int GetMaxDrawableDigitWidth(void) { return max_digit_width_; }

	// オフセット値を設定する
	void SetOffestWidth(int offsetWidth) { offset_width_ = offsetWidth; }


private:
	// 最大桁数
	static constexpr int MAX_DIGIT_LENGTH = 8;

	//テクスチャの分割数
	static constexpr int texture_width_divisions = 5;
	static constexpr int texture_height_divisions = 2;

	// 表示する桁数のスプライト
	class SpriteRendererComponent* sprite_digit_[MAX_DIGIT_LENGTH];

	// 設定するテクスチャの種類
	enum class TextureType texture_type_;

	// 描画座標を中心にするか
	bool is_drawing_position_to_center_;

	// フォントテクスチャのUV座標の原点
	bool is_font_texture_uv_origin_zero_;

	//色情報
	int red_;
	int green_;
	int blue_;
	int alpha_;

	// 描画桁数
	int drawable_digit_length_;

	// フォントの幅と高さ
	int font_width_;
	int font_height_;

	//描画する桁の最大の横幅
	int max_digit_width_;

	// 桁数字間での文字のオフセット値
	int offset_width_;

	// 数字データ
	int int_data_;
};

#endif //SPRITE_DIGIT_RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/