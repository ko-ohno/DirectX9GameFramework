/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Math.cpp] 数学ライブラリ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：数学ライブラリを定義
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "Math.h"

/*-------------------------------------
/* 数学ライブラリの定義
-------------------------------------*/
namespace Math
{

	/*-----------------------------------------------------------------------------
	/* 2次元ベクトルクラス
	-----------------------------------------------------------------------------*/
	//静的定数宣言
	const Vector2 Vector2::ZERO(0.0f, 0.0f);
	const Vector2 Vector2::UP(0.0f, 1.0f);
	const Vector2 Vector2::DAWN(0.0f, -1.0f);
	const Vector2 Vector2::RIGHT(1.0f, 0.0f);
	const Vector2 Vector2::LEFT(-1.0f, 0.0f);

	/*-------------------------------------
	/* 以下計算ライブラリ群
	-------------------------------------*/
	//2次元ベクトルの内積計算
	float Vector2::Dot(const Vector2& other) const
	{
		return (x_ * other.x_) + (y_ * other.y_);
	}

	//2次元ベクトルの外積計算
	float Vector2::Cross(const Vector2& other) const
	{
		return (x_ * other.y_) - (y_ * other.x_);
	}

	//2次元ベクトルの長さ
	float Vector2::Length(void) const
	{
		//std::sqrtは平方根の関数
		return std::sqrt(Dot(*this));
	}

	//距離
	float Vector2::Distance(const Vector2& other) const
	{
		return (*this - other).Length();
	}

	//正規化
	Vector2 Vector2::Normalize(void) const
	{
		const float vec_length = Length();
		if (vec_length < FLT_EPSILON)
		{
			return Vector2::ZERO;
		}
		return *this / vec_length;
	}

	//ゼロベクトルか
	bool Vector2::IsZero(void) const
	{
		return *this == Vector2::ZERO;
	}

	/*-----------------------------------------------------------------------------
	/* 3次元ベクトルクラス
	-----------------------------------------------------------------------------*/
	//静的定数宣言
	const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UP(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::DAWN(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::RIGHT(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::LEFT(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::FRONT(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::BACK(0.0f, 0.0f, -1.0f);

	/*-------------------------------------
	/* 以下計算ライブラリ群
	-------------------------------------*/
	//3次元ベクトルの内積計算
	float Vector3::Dot(const Vector3& other) const
	{
		return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_);
	}

	//3次元ベクトルの外積計算
	Vector3 Vector3::Cross(const Vector3& other) const
	{
		// X = src.Y * dst.Z - src.Z * dst.Y
		// Y = src.Z * dst.X - src.X * dst.Z
		// Z = src.X * dst.Y - src.Y * dst.Y
		Vector3 ret_value;
		ret_value.x_ = (y_ * other.z_) - (z_ * other.y_);
		ret_value.y_ = (z_ * other.x_) - (x_ * other.z_);
		ret_value.z_ = (x_ * other.y_) - (y_ * other.x_);
		return ret_value;
	}

	//3次元ベクトルの外積計算
	float Vector3::Length(void) const
	{
		//std::sqrtは平方根の関数
		return std::sqrt(Dot(*this));
	}

	//距離
	float Vector3::Distance(const Vector3& other) const
	{
		return (*this - other).Length();
	}

	//正規化
	Vector3 Vector3::Normalize(void) const
	{
		const float vec_length = Length();
		if (vec_length < FLT_EPSILON)
		{
			return Vector3::ZERO;
		}
		return *this / vec_length;
	}

	//ゼロベクトルか
	bool Vector3::isZero(void) const
	{
		return *this == Vector3::ZERO;
	}

	/*-----------------------------------------------------------------------------
	/* イージング関数群
	-----------------------------------------------------------------------------*/

	// currentTime  現在時刻
	// totalTime	値が、最小値から最大値までに到達するまでの、現在時刻の上限となる合計時間
	// min			最小値
	// max			最大値

	/*-------------------------------------
	/* イージング関数:Linear
	-------------------------------------*/

	float Easing::Linear(float currentTime, float totalTime, float min, float max)
	{
		return (max - min) * currentTime / totalTime + min;
	}

	/*-------------------------------------
	/* イージング関数:Sine
	-------------------------------------*/

	float Easing::SineIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		return -max * Math::Cos(currentTime * (Math::PI * 90 / 180) / totalTime) + max + min;
	}

	float Easing::SineOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		return max * Math::Sin(currentTime * (Math::PI * 90 / 180) / totalTime) + min;
	}

	float Easing::SineInOut(float currentTime, float toralTime, float min, float max)
	{
		max -= min;
		return -max / 2 * (Math::Cos(currentTime * Math::PI / toralTime) - 1) + min;
	}

	/*-------------------------------------
	/* イージング関数:Quad
	-------------------------------------*/

	float Easing::QuadIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;
		return max * currentTime * currentTime + min;
	}

	float Easing::QuadOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;
		return -max * currentTime * (currentTime - 2) + min;
	}

	float Easing::QuadInOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime / 2;
		if (currentTime < 1) return max / 2 * currentTime * currentTime + min;

		currentTime = currentTime - 1;
		return -max / 2 * (currentTime * (currentTime - 2) - 1) + min;
	}

	/*-------------------------------------
	/* イージング関数:Cubic
	-------------------------------------*/

	float Easing::CubicIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;
		return max * currentTime * currentTime * currentTime + min;
	}

	float Easing::CubicOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime = currentTime / totalTime - 1;
		return max * (currentTime * currentTime * currentTime + 1) + min;
	}

	float Easing::CubicInOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime / 2;
		if (currentTime < 1) return max / 2 * currentTime * currentTime * currentTime + min;

		currentTime = currentTime - 2;
		return max / 2 * (currentTime * currentTime * currentTime + 2) + min;
	}

	/*-------------------------------------
	/* イージング関数:Quart
	-------------------------------------*/

	float Easing::QuartIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;
		return max * currentTime * currentTime * currentTime * currentTime + min;
	}

	float Easing::QuartOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime = currentTime / totalTime - 1;
		return -max * (currentTime * currentTime * currentTime * currentTime - 1) + min;
	}

	float Easing::QuartInOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime / 2;
		if (currentTime < 1) return max / 2 * currentTime * currentTime * currentTime * currentTime + min;

		currentTime = currentTime - 2;
		return -max / 2 * (currentTime * currentTime * currentTime * currentTime - 2) + min;
	}

	/*-------------------------------------
	/* イージング関数:Quint
	-------------------------------------*/

	float Easing::QuintIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;
		return max * currentTime * currentTime * currentTime * currentTime * currentTime + min;
	}

	float Easing::QuintOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime = currentTime / totalTime - 1;
		return max * (currentTime * currentTime * currentTime * currentTime * currentTime + 1) + min;
	}

	float Easing::QuintInOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime / 2;
		if (currentTime < 1) return max / 2 * currentTime * currentTime * currentTime * currentTime * currentTime + min;

		currentTime = currentTime - 2;
		return max / 2 * (currentTime * currentTime * currentTime * currentTime * currentTime + 2) + min;
	}

	/*-------------------------------------
	/* イージング関数:Expo
	-------------------------------------*/

	float Easing::ExpoIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		return currentTime == 0.0 ? min : max * Math::Pow(2, 10 * (currentTime / totalTime - 1)) + min;
	}

	float Easing::ExpoOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		return currentTime == totalTime ? max + min : max * (-Math::Pow(2, -10 * currentTime / totalTime) + 1) + min;
	}

	float Easing::ExpoInOut(float currentTime, float totalTime, float min, float max)
	{
		if (currentTime == 0.0f) return min;
		if (currentTime == totalTime) return max;
		max -= min;
		currentTime /= totalTime / 2;

		if (currentTime < 1) return max / 2 * Math::Pow(2, 10 * (currentTime - 1)) + min;

		currentTime = currentTime - 1;
		return max / 2 * (-Math::Pow(2, -10 * currentTime) + 2) + min;
	}

	/*-------------------------------------
	/* イージング関数:Circ
	-------------------------------------*/

	float Easing::CircIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;
		return -max * (Math::Sqrt(1 - currentTime * currentTime) - 1) + min;
	}

	float Easing::CircOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime = currentTime / totalTime - 1;
		return max * Math::Sqrt(1 - currentTime * currentTime) + min;
	}

	float Easing::CircInOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime / 2;
		if (currentTime < 1) return -max / 2 * (Math::Sqrt(1 - currentTime * currentTime) - 1) + min;

		currentTime = currentTime - 2;
		return max / 2 * (Math::Sqrt(1 - currentTime * currentTime) + 1) + min;
	}

	/*-------------------------------------
	/* イージング関数:Back
	-------------------------------------*/

	float Easing::BackIn(float currentTime, float totalTime, float min, float max, float speed)
	{
		max -= min;
		currentTime /= totalTime;
		return max * currentTime * currentTime * ((speed + 1) * currentTime - speed) + min;
	}

	float Easing::BackOut(float currentTime, float totalTime, float min, float max, float speed)
	{
		max -= min;
		currentTime = currentTime / totalTime - 1;
		return max * (currentTime * currentTime * ((speed + 1) * currentTime + speed) + 1) + min;
	}

	float Easing::BackInOut(float currentTime, float totalTime, float min, float max, float speed)
	{
		max -= min;
		speed *= 1.525f;
		currentTime /= totalTime / 2;
		if (currentTime < 1) return max / 2 * (currentTime * currentTime * ((speed + 1) * currentTime - speed)) + min;

		currentTime = currentTime - 2;
		return max / 2 * (currentTime * currentTime * ((speed + 1) * currentTime + speed) + 2) + min;
	}

	/*-------------------------------------
	/* イージング関数:Elastic
	-------------------------------------*/

	float Easing::ElasticIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;

		float s = 1.70158f;
		float p = totalTime * 0.3f;
		float a = max;

		if (currentTime == 0) return min;
		if (currentTime == 1) return min + max;

		if (a < Math::Abs(max))
		{
			a = max;
			s = p / 4;
		}
		else
		{
			s = p / (2 * Math::PI) * Math::Asin(max / a);
		}

		currentTime = currentTime - 1;
		return -(a * Math::Pow(2, 10 * currentTime) * Math::Sin((currentTime * totalTime - s) * (2 * Math::PI) / p)) + min;
	}

	float Easing::ElasticOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime;

		float s = 1.70158f;
		float p = totalTime * 0.3f; ;
		float a = max;

		if (currentTime == 0) return min;
		if (currentTime == 1) return min + max;

		if (a < Math::Abs(max))
		{
			a = max;
			s = p / 4;
		}
		else
		{
			s = p / (2 * Math::PI) * Math::Asin(max / a);
		}

		return a * Math::Pow(2, -10 * currentTime) * Math::Sin((currentTime * totalTime - s) * (2 * Math::PI) / p) + max + min;
	}

	float Easing::ElasticInOut(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		currentTime /= totalTime / 2;

		float s = 1.70158f;
		float p = totalTime * (0.3f * 1.5f);
		float a = max;

		if (currentTime == 0) return min;
		if (currentTime == 2) return min + max;

		if (a < Math::Abs(max))
		{
			a = max;
			s = p / 4;
		}
		else
		{
			s = p / (2 * Math::PI) * Math::Asin(max / a);
		}

		if (currentTime < 1)
		{
			return -0.5f * (a * Math::Pow(2, 10 * (currentTime -= 1)) * Math::Sin((currentTime * totalTime - s) * (2 * Math::PI) / p)) + min;
		}

		currentTime = currentTime - 1;
		return a * Math::Pow(2, -10 * currentTime) * Math::Sin((currentTime * totalTime - s) * (2 * Math::PI) / p) * 0.5f + max + min;
	}

	/*-------------------------------------
	/* イージング関数:Bounce
	-------------------------------------*/

	float Easing::BounceIn(float currentTime, float totalTime, float min, float max)
	{
		max -= min;
		return max - BounceOut(totalTime - currentTime, totalTime, 0, max) + min;
	}

	float Easing::BounceOut(float currentTime, float totalTime, float min, float max)
	{

		max -= min;
		currentTime /= totalTime;

		if (currentTime < 1.0f / 2.75f)
		{
			return max * (7.5625f * currentTime * currentTime) + min;
		}
		else if (currentTime < 2.0f / 2.75f)
		{
			currentTime -= 1.5f / 2.75f;
			return max * (7.5625f * currentTime * currentTime + 0.75f) + min;
		}
		else if (currentTime < 2.5f / 2.75f)
		{
			currentTime -= 2.25f / 2.75f;
			return max * (7.5625f * currentTime * currentTime + 0.9375f) + min;
		}
		else
		{
			currentTime -= 2.625f / 2.75f;
			return max * (7.5625f * currentTime * currentTime + 0.984375f) + min;
		}
	}

	float Easing::BounceInOut(float currentTime, float totalTime, float min, float max)
	{
		if (currentTime < totalTime / 2)
		{
			return BounceIn(currentTime * 2, totalTime, 0, max - min) * 0.5f + min;
		}
		else
		{
			return BounceOut(currentTime * 2 - totalTime, totalTime, 0, max - min) * 0.5f + min + (max - min) * 0.5f;
		}
	}
}

/*=============================================================================
/*		End of File
=============================================================================*/