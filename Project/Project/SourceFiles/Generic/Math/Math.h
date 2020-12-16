#pragma once


namespace Math
{
	//‰~ü—¦‚Ì’è‹`
	template<typename T>
	constexpr T PI = static_cast<T>(3.14159265359L);

	//‚ ‚Ó‚ê‚½‰~ü—¦(Šp“x)‚Ì³‹K‰»ƒ}ƒNƒŠÖ”
	template<typename T>
	static const T pi_normalize(T num)
	{
		if (num >= PI<float>) { num = 0; }
		return num;
	};

};