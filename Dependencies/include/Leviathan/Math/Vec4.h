#pragma once

#include <Leviathan/Math/Leviamath.h>

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

	DLL Vec4();
	DLL Vec4(float _val);
	DLL Vec4(float _x, float _y, float _z);
	DLL Vec4(float _x, float _y, float _z, float _w);
	DLL Vec4(initializer_list<float> _values);

	DLL float Magnitude() const;
	DLL float SqrMagnitude() const;
	DLL Vec4 Normalised() const;

	DLL void Normalise();

	DLL static Vec4 Normalise(Vec4 _vec);
	DLL static float Dot(Vec4 _lhs, Vec4 _rhs);

};