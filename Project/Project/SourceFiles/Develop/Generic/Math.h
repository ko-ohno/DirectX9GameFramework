/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Math.h] 数学ライブラリ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：数学ライブラリを定義
=============================================================================*/
#ifndef MATH_H_
#define	MATH_H_

/*--- インクルードファイル ---*/

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* 数学ライブラリ
-------------------------------------*/
namespace Math
{
	//円周率の定義
	constexpr float PI = 3.14159265359f;
	constexpr float TwoPI = PI * 2.0f;

	//もう一度同じ方向を向くには、360度分回転が必要
	//ラジアン = 角度 * (π(3.14f) / 角度(180))
	//ラジアンに回転値(円周)を代入
	///角度への円周へ
	inline float ToRadian(int degree)
	{
		return (float)(degree * (PI / 180));
	}

	//もう一度同じ方向を向くには、6.28f分回転が必要
	//角度  = ラジアン * (角度(180) / π(3.14f))
	//ラジアンに回転値(円周)を代入
	///円周から角度へ
	inline int ToDegree(float radian)
	{
		return (int)(radian * (180 / PI));
	}

	//0の絶対値をとる
	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return std::max(a, b);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return std::min(a, b);
	}

	//クランプ処理
	template<typename T>
	inline T Clamp(T value, T low, T high)
	{
		return std::min(std::max(value, low), high);
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);
	}

	inline float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Asin(float value)
	{
		return asin(value);
	}

	inline float Atan(float value)
	{
		return atanf(value);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Pow(float value, float exponent)
	{
		return pow(value, exponent);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float src, float dst, float time)
	{
		return (1 - time) * src + time * dst;
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)
	{
		return fmod(numer, denom);
	}
}

/*-------------------------------------
/* 2次元ベクトルクラス
-------------------------------------*/
class Vector2
{
public:
	float x_;
	float y_;

public:
	//コンストラクタ
	Vector2(void) : x_(0.0f), y_(0.0f) {}
	Vector2(const float x, const float y) : x_(x), y_(y) {}
	Vector2(D3DXVECTOR2& d3dxVec2) : x_(d3dxVec2.x), y_(d3dxVec2.y) {}
	Vector2(const D3DXVECTOR2& d3dxVec2) : x_(d3dxVec2.x), y_(d3dxVec2.y) {}

	//デストラクタ
	~Vector2(void) {}

	//各計算処理

	//2次元ベクトルの内積計算
	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return (v1.x_ * v2.x_) + (v1.y_ * v2.y_);
	}

	//2次元ベクトルの外積計算
	static float Cross(const Vector2& v1, const Vector2& v2)
	{
		return (v1.x_ * v2.y_) - (v1.y_ * v2.x_);
	}

	//2次元ベクトルの線形補完
	static Vector2 Vector2lerp(const Vector2& src, const Vector2& dst, float time)
	{
		Vector2 src_vector = src;
		Vector2 dst_vector = dst;
		float x = (1 - time) * src_vector.x_ + time * dst_vector.x_;
		float y = (1 - time) * src_vector.y_ + time * dst_vector.y_;
		return Vector2(x, y);
	}

	//インスタンスが自分と相手の場合の計算

	//2次元ベクトルの内積計算
	float Dot(const Vector2& other) const;

	//2次元ベクトルの外積計算
	float Cross(const Vector2& other) const;

	//ベクトルの長さ
	float Length(void) const;

	//座標までの長さ
	float Distance(const Vector2& other) const;

	//正規化
	Vector2 Normalize(void) const;

	//ゼロベクトルか
	bool IsZero(void) const;

	//演算子のオーバーロード

	//Vector2 +=
	inline Vector2& operator += (const Vector2& other)
	{
		return *this = *this + other;
	}

	//Vector2 -=
	inline Vector2& operator -= (const Vector2& other)
	{
		return *this = *this - other;
	}

	//Scaler *=
	inline Vector2& operator *= (float fScaler)
	{
		return *this = *this * fScaler;
	}

	//Scaler /=
	inline Vector2& operator /= (float fScaler)
	{
		return *this = *this / fScaler;
	}

	//Vector2 +
	inline const Vector2 operator + (const Vector2& other) const
	{
		return Vector2(x_ + other.x_, y_ + other.y_);
	}

	//Vector2 - 
	inline const Vector2 operator - (const Vector2& other) const
	{
		return Vector2(x_ - other.x_, y_ - other.y_);
	}

	//Scaler *
	inline const Vector2 operator * (float fScaler) const
	{
		return Vector2(x_ * fScaler, y_ * fScaler);
	}

	//Scaler /
	inline const Vector2 operator / (float fScaler) const
	{
		return Vector2(x_ / fScaler, y_ / fScaler);
	}

	//Vector2 + code
	inline const Vector2 operator + (void) const
	{
		return Vector2(+x_, +y_);
	}

	//Vector2 - code
	inline const Vector2 operator - (void) const
	{
		return Vector2(-x_, -y_);
	}

	//Vector2 ==
	inline bool operator == (const Vector2& other) const
	{
		return (x_ == other.x_) && (y_ == other.y_);
	}

	//Vector2 !=
	inline bool operator != (const Vector2& other) const
	{
		return !(*this == other);
	}

	//Vector2 <
	inline bool operator < (const Vector2& other) const
	{
		if (x_ < other.x_) { return true; }
		if (y_ < other.y_) { return true; }
		return false;
	}

	//Vector2 >
	inline bool operator > (const Vector2& other) const
	{
		if (x_ > other.x_) { return true; }
		if (y_ > other.y_) { return true; }
		return false;
	}

	//Vector2 <=
	inline bool operator <= (const Vector2& other) const
	{
		if (x_ <= other.x_) { return true; }
		if (y_ <= other.y_) { return true; }
		return false;
	}

	//Vector2 >=
	inline bool operator >= (const Vector2& other) const
	{
		if (x_ >= other.x_) { return true; }
		if (y_ >= other.y_) { return true; }
		return false;
	}

	//定数宣言
	static const Vector2 ZERO;
	static const Vector2 UP;
	static const Vector2 DAWN;
	static const Vector2 RIGHT;
	static const Vector2 LEFT;
private:
};

/*-------------------------------------
/* 3次元ベクトルクラス
-------------------------------------*/
class Vector3
{
public:
	float x_;
	float y_;
	float z_;

public:
	//コンストラクタ
	Vector3(void) : x_(0.0f), y_(0.0f), z_(0.0f) {}
	Vector3(const float x, const float y, const float z) : x_(x), y_(y), z_(z) {}
	Vector3(D3DXVECTOR3& d3dxVec3) : x_(d3dxVec3.x), y_(d3dxVec3.y), z_(d3dxVec3.z) {}
	Vector3(const D3DXVECTOR3& d3dxVec3) : x_(d3dxVec3.x), y_(d3dxVec3.y), z_(d3dxVec3.z) {}

	//デストラクタ
	~Vector3(void) {}

	//各計算処理

	//3次元ベクトルの内積計算
	static float Dot(const Vector3& v1, const Vector3& v2)
	{
		return (v1.x_ * v2.x_) + (v1.y_ * v2.y_) + (v1.z_ * v2.z_);
	}

	//3次元ベクトルの外積計算
	static Vector3 Cross(const Vector3& v1, const Vector3& v2)
	{
		// X = src.Y * dst.Z - src.Z * dst.Y
		// Y = src.Z * dst.X - src.X * dst.Z
		// Z = src.X * dst.Y - src.Y * dst.Y
		Vector3 ret_value;
		ret_value.x_ = (v1.y_ * v2.z_) - (v1.z_ * v2.y_);
		ret_value.y_ = (v1.z_ * v2.x_) - (v1.x_ * v2.z_);
		ret_value.z_ = (v1.x_ * v2.y_) - (v1.y_ * v2.x_);
		return ret_value;
	}

	//3次元ベクトルの線形補完
	static Vector3 Vector3lerp(const Vector3& src, const Vector3& dst, float time)
	{
		Vector3 src_vector = src;
		Vector3 dst_vector = dst;
		float x = (1 - time) * src_vector.x_ + time * dst_vector.x_;
		float y = (1 - time) * src_vector.y_ + time * dst_vector.y_;
		float z = (1 - time) * src_vector.z_ + time * dst_vector.z_;
		return Vector3(x, y, z);
	}

	//インスタンスが自分と相手の場合の計算
		
	//内積計算
	float Dot(const Vector3& other) const;
		
	//外積計算
	Vector3 Cross(const Vector3& other) const;
		
	//ベクトルの長さ
	float Length(void) const;
		
	//座標までの長さ
	float Distance(const Vector3& other) const;
		
	//ベクトルの正規化
	Vector3 Normalize(void) const;

	//ゼロベクトルか？
	bool isZero(void) const;

	//演算子のオーバーロード
		
	//Vector3 +=
	inline Vector3& operator += (const Vector3& other)
	{
		return *this = *this + other;
	}

	//Vector3 -=
	inline Vector3& operator -= (const Vector3& other)
	{
		return *this = *this - other;
	}

	//Vector3 *=
	inline Vector3& operator *= (float fScaler)
	{
		return *this = *this * fScaler;
	}

	//Vector3 /=
	inline Vector3& operator /= (float fScaler)
	{
		return *this = *this / fScaler;
	}

	//Vector3 +
	inline const Vector3 operator + (const Vector3& other) const
	{
		return Vector3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
	}

	//Vector3 -
	inline const Vector3 operator - (const Vector3& other) const
	{
		return Vector3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
	}

	//Scaler /
	inline const Vector3 operator * (float fScaler) const
	{
		return Vector3(x_ * fScaler, y_ * fScaler, z_ * fScaler);
	}

	//Scaler /
	inline const Vector3 operator / (float fScaler) const
	{
		return Vector3(x_ / fScaler, y_ / fScaler, z_ / fScaler);
	}

	//Vector3 + code
	inline const Vector3 operator + (void) const
	{
		return Vector3(+x_, +y_, +z_);
	}

	//Vector3 - code
	inline const Vector3 operator - (void) const
	{
		return Vector3(-x_, -y_, -z_);
	}

	//Vector3 ==
	inline bool operator == (const Vector3& other) const
	{
		return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
	}

	//Vector3 !=
	inline bool operator != (const Vector3& other) const
	{
		return !(*this == other);
	}

	//Vector3 <
	inline bool operator < (const Vector3& other) const
	{
		if (x_ < other.x_) { return true; }
		if (y_ < other.y_) { return true; }
		if (z_ < other.z_) { return true; }
		return false;
	}

	//Vector3 >
	inline bool operator > (const Vector3& other) const
	{
		if (x_ > other.x_) { return true; }
		if (y_ > other.y_) { return true; }
		if (z_ > other.z_) { return true; }
		return false;
	}
		
	//Vector3 <=
	inline bool operator <= (const Vector3& other) const
	{
		if (x_ <= other.x_) { return true; }
		if (y_ <= other.y_) { return true; }
		if (z_ <= other.z_) { return true; }
		return false;
	}

	//Vector3 >=
	inline bool operator >= (const Vector3& other) const
	{
		if (x_ >= other.x_) { return true; }
		if (y_ >= other.y_) { return true; }
		if (z_ >= other.z_) { return true; }
		return false;
	}

	//定数宣言
	static const Vector3 ZERO;
	static const Vector3 UP;
	static const Vector3 DAWN;
	static const Vector3 RIGHT;
	static const Vector3 LEFT;
	static const Vector3 FRONT;
	static const Vector3 BACK;
private:
};

/*-------------------------------------
/* イージング関数群
-------------------------------------*/
namespace Easing
{
	//イージングのwebサンプル
	//https://easings.net/ja

	// currentTime  現在時刻
	// totalTime	値が、最小値から最大値までに到達するまでの、現在時刻の上限となる合計時間
	// min			最小値
	// max			最大値

	// Liner
		float Linear(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Sine
	float SineIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float SineOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float SineInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Quad
	float QuadIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float QuadOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float QuadInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Cubic
	float CubicIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float CubicOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float CubicInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Quart
	float QuartIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float QuartOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float QuartInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Quint
	float QuintIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float QuintOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float QuintInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Expo
	float ExpoIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float ExpoOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float ExpoInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Circ
	float CircIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float CircOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float CircInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Back
	float BackIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f, float speed = 1.f);
	float BackOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f, float speed = 1.f);
	float BackInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f, float speed = 1.f);

	// Elastic
	float ElasticIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float ElasticOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float ElasticInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);

	// Bounce
	float BounceIn(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float BounceOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
	float BounceInOut(float currentTime = 0.0f, float totalTime = 1.f, float min = 0.f, float max = 1.f);
}

#endif //MATH_H_
/*=============================================================================
/*		End of File
=============================================================================*/