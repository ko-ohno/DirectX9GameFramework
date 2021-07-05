/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SpriteDigitRendererComponent.cpp] スプライトの桁数描画コンポーネントクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトの桁数描画コンポーネントクラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../../../../../StdAfx.h"
#include "SpriteDigitRendererComponent.h"
#include "SpriteRendererComponent.h"
#include "../../GameObject.h"

/*---------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
SpriteDigitRendererComponent::SpriteDigitRendererComponent(class GameObject* owner, int drawOrder)
	: RendererComponent(owner, drawOrder)
	, texture_type_(TextureType::None)
	, is_drawing_position_to_center_(false)
	, is_font_texture_uv_origin_zero_(false)
	, red_(255)
	, green_(255)
	, blue_(255)
	, alpha_(255)
	, font_width_(0)
	, font_height_(0)
	, max_digit_width_(0)
	, offset_width_(0)
	, drawable_digit_length_(0)
	, int_data_(0)
{
	const bool is_init_sprite_digit_renderer = this->Init();
	if (is_init_sprite_digit_renderer == false)
	{
		assert(!"スプライトの桁数レンダラーの初期化に失敗した");
	}
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
SpriteDigitRendererComponent::~SpriteDigitRendererComponent(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* 初期化処理
-----------------------------------------------------------------------------*/
bool SpriteDigitRendererComponent::Init(void)
{
	//描画シェーダーの指定
	this->shader_type_ = ShaderType::Sprite;

	// 初期化
	{
		//オフセットしたよこ幅の値
		offset_width_ = 25;

		// 時の幅と高さ
		font_width_			   =  90;
		font_height_		   = 100;

		// 描画する桁数字の長さ
		drawable_digit_length_ = 8;

		// 数字データ
		int_data_ = 0;
	}

	// 桁数描画コンポーネントの初期化
	{
		for (int i = 0; i < MAX_DIGIT_LENGTH; i++)
		{
			// インスタンス生成
			sprite_digit_[i] = NEW SpriteRendererComponent(owner_);
			sprite_digit_[i]->SetScaleX(static_cast<float>(font_width_));
			sprite_digit_[i]->SetScaleY(static_cast<float>(font_height_));

			// 描画するかの設定
			if (i <= drawable_digit_length_ -1)
			{
				sprite_digit_[i]->IsSetDrawable(false);
			}
		}
	}
	return true;
}

/*-----------------------------------------------------------------------------
/* 終了化処理
-----------------------------------------------------------------------------*/
void SpriteDigitRendererComponent::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* 更新処理
-----------------------------------------------------------------------------*/
void SpriteDigitRendererComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	// エラーチェック
	{
		// 描画する桁数が最大を上回っていたら
		if (drawable_digit_length_ >= MAX_DIGIT_LENGTH)
		{
			assert(!"SpriteDigitRendererComponent::Update():描画する桁数が最大：8を上回っています！");
		}

		// テクスチャが設定されているか
		if (texture_type_ == TextureType::None)
		{
			assert(!"SpriteDigitRendererComponent::Update():テクスチャが設定されていません！");
		}

	}

	// テクスチャ情報を設定
	for (int i = 0; i < MAX_DIGIT_LENGTH; i++)
	{
		sprite_digit_[i]->SetTexture(texture_type_);
	}

	// 桁の中央から端までの横幅
	const float digit_center_width = (font_width_ * drawable_digit_length_) / 2.f;


	// テクスチャの幅と高さ
	const int texture_width = sprite_digit_[0]->GetTextureImageInfo()->Width;
	const int texture_height = sprite_digit_[0]->GetTextureImageInfo()->Height ;

	// テクスチャの切り取りサイズ
	const int texture_cut_width = (texture_width / texture_width_divisions);
	const int texture_cut_height = (texture_height / texture_height_divisions);
	

	// 数値の計算
	int draw_digit_value = 0;

	//倍率
	int magnification = 10; //scoreを10^N(累乗)で割るための変数。

	//余剰の倍率
	int surplus_magnification = 1; //n桁目の値を割った余りから計算する変数

	// 文字の更新
	for (int i = 0; i < MAX_DIGIT_LENGTH; i++)
	{
		// 描画するかを設定する
		if (i <= drawable_digit_length_ - 1)
		{
			sprite_digit_[i]->IsSetDrawable(true);
		}
		else
		{
			sprite_digit_[i]->IsSetDrawable(false);
		}

		// 描画しなかったら更新しない
		if (sprite_digit_[i]->IsGetDrawable() == false)
		{
			break;
		}

		// 数値の計算
		{
			//桁の余りの計算
			draw_digit_value = int_data_ % magnification;	//score_をmagnificationのｎ桁で割った余りを代入する。
			draw_digit_value /= surplus_magnification;		//score_(割った余り)をsurplus_magnificationで割れた数を代入する。
		}

		// 拡縮率の更新
		{
			sprite_digit_[i]->SetScaleX(static_cast<float>(font_width_));
			sprite_digit_[i]->SetScaleY(static_cast<float>(font_height_));
			sprite_digit_[i]->IsSetDrawingPositionToCenter(is_drawing_position_to_center_);
		}

		// ポリゴンカラーの更新
		{
			sprite_digit_[i]->SetVertexColor(red_, green_, blue_, alpha_);
		}

		// UV座標の計算
		{
			//int draw_digit_value = i;

			if (is_font_texture_uv_origin_zero_ == true)
			{
				//valueが0の時、テクスチャのUV座標を数字の"0"がある位置までもっていく。
				if (draw_digit_value == 0)
				{
					draw_digit_value = 9; //"0"があるUV座標の番号
				}
				else
				{
					draw_digit_value -= 1; //最初に数字の"0"がない分だけ1つずつずれる。
				}
			}

			sprite_digit_[i]->SetUVAnimation(texture_cut_width * (draw_digit_value % 5)
											, texture_cut_height * (draw_digit_value / 5)
											, texture_cut_width
											, texture_cut_height);
		}

		// 描画座標の計算
		{
			// フォント間の行間
			const int font_padding_width = font_width_ - offset_width_;

			// 各桁の幅
			max_digit_width_ = font_padding_width * drawable_digit_length_;

			// 全体の長さから引いていく
			const float draw_pos_x = position_.x + (max_digit_width_ - (font_padding_width * (i + 1)));
			const float draw_pos_y = position_.y;

			// 座標の設定
			sprite_digit_[i]->SetTranslationX(draw_pos_x);
			sprite_digit_[i]->SetTranslationY(draw_pos_y);
		}

		// 数値の計算
		{
			//最後にそれぞれ10倍にして、一つ上の位へ桁を繰り上げる。
			magnification *= 10;
			surplus_magnification *= 10;
		}
	}
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
//void SpriteDigitRendererComponent::Draw(Shader* shader, Camera* camera)
//{
//		SpriteRendererComponentを使用しているので描画処理は必要ない
//}

/*=============================================================================
/*		End of File
=============================================================================*/