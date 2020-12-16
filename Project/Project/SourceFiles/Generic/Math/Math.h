#pragma once


namespace Math
{
	//�~�����̒�`
	template<typename T>
	constexpr T PI = static_cast<T>(3.14159265359L);

	//���ӂꂽ�~����(�p�x)�̐��K���}�N���֐�
	template<typename T>
	static const T pi_normalize(T num)
	{
		if (num >= PI<float>) { num = 0; }
		return num;
	};

};