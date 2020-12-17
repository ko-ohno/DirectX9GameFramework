/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Math.cpp] ���w���C�u����
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���w���C�u�������`
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "Math.h"

/*-------------------------------------
/* ���w���C�u�����̒�`
-------------------------------------*/
namespace Math
{

	/*-----------------------------------------------------------------------------
	/* 2�����x�N�g���N���X
	-----------------------------------------------------------------------------*/
	//�ÓI�萔�錾
	const Vector2 Vector2::ZERO(0.0f, 0.0f);
	const Vector2 Vector2::UP(0.0f, 1.0f);
	const Vector2 Vector2::DAWN(0.0f, -1.0f);
	const Vector2 Vector2::RIGHT(1.0f, 0.0f);
	const Vector2 Vector2::LEFT(-1.0f, 0.0f);

	/*-------------------------------------
	/* �ȉ��v�Z���C�u�����Q
	-------------------------------------*/
	//2�����x�N�g���̓��όv�Z
	float Vector2::Dot(const Vector2& other) const
	{
		return (x_ * other.x_) + (y_ * other.y_);
	}

	//2�����x�N�g���̊O�όv�Z
	float Vector2::Cross(const Vector2& other) const
	{
		return (x_ * other.y_) - (y_ * other.x_);
	}

	//2�����x�N�g���̒���
	float Vector2::Length(void) const
	{
		//std::sqrt�͕������̊֐�
		return std::sqrt(Dot(*this));
	}

	//����
	float Vector2::Distance(const Vector2& other) const
	{
		return (*this - other).Length();
	}

	//���K��
	Vector2 Vector2::Normalize(void) const
	{
		const float vec_length = Length();
		if (vec_length < FLT_EPSILON)
		{
			return Vector2::ZERO;
		}
		return *this / vec_length;
	}

	//�[���x�N�g����
	bool Vector2::IsZero(void) const
	{
		return *this == Vector2::ZERO;
	}

	/*-----------------------------------------------------------------------------
	/* 3�����x�N�g���N���X
	-----------------------------------------------------------------------------*/
	//�ÓI�萔�錾
	const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UP(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::DAWN(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::RIGHT(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::LEFT(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::FRONT(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::BACK(0.0f, 0.0f, -1.0f);

	/*-------------------------------------
	/* �ȉ��v�Z���C�u�����Q
	-------------------------------------*/
	//3�����x�N�g���̓��όv�Z
	float Vector3::Dot(const Vector3& other) const
	{
		return (x_ * other.x_) + (y_ * other.y_) + (z_ * other.z_);
	}

	//3�����x�N�g���̊O�όv�Z
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

	//3�����x�N�g���̊O�όv�Z
	float Vector3::Length(void) const
	{
		//std::sqrt�͕������̊֐�
		return std::sqrt(Dot(*this));
	}

	//����
	float Vector3::Distance(const Vector3& other) const
	{
		return (*this - other).Length();
	}

	//���K��
	Vector3 Vector3::Normalize(void) const
	{
		const float vec_length = Length();
		if (vec_length < FLT_EPSILON)
		{
			return Vector3::ZERO;
		}
		return *this / vec_length;
	}

	//�[���x�N�g����
	bool Vector3::isZero(void) const
	{
		return *this == Vector3::ZERO;
	}

	/*-----------------------------------------------------------------------------
	/* �C�[�W���O�֐��Q
	-----------------------------------------------------------------------------*/

	// currentTime  ���ݎ���
	// totalTime	�l���A�ŏ��l����ő�l�܂łɓ��B����܂ł́A���ݎ����̏���ƂȂ鍇�v����
	// min			�ŏ��l
	// max			�ő�l

	/*-------------------------------------
	/* �C�[�W���O�֐�:Linear
	-------------------------------------*/

	float Easing::Linear(float currentTime, float totalTime, float min, float max)
	{
		return (max - min) * currentTime / totalTime + min;
	}

	/*-------------------------------------
	/* �C�[�W���O�֐�:Sine
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
	/* �C�[�W���O�֐�:Quad
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
	/* �C�[�W���O�֐�:Cubic
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
	/* �C�[�W���O�֐�:Quart
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
	/* �C�[�W���O�֐�:Quint
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
	/* �C�[�W���O�֐�:Expo
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
	/* �C�[�W���O�֐�:Circ
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
	/* �C�[�W���O�֐�:Back
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
	/* �C�[�W���O�֐�:Elastic
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
	/* �C�[�W���O�֐�:Bounce
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