#pragma once

#include <initializer_list>

#define VEC_4_LENGTH 4

using std::initializer_list;

struct Vec4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float values[VEC_4_LENGTH];
	};

	Vec4();
	Vec4(float _val);
	Vec4(float _x, float _y, float _z);
	Vec4(float _x, float _y, float _z, float _w);
	Vec4(initializer_list<float> _values);

	float Magnitude() const;
	float SqrMagnitude() const;
	Vec4 Normalised() const;

	void Normalise();

	static Vec4 Normalise(Vec4 _vec);
	static float Dot(Vec4 _lhs, Vec4 _rhs);

};