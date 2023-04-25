#pragma once

#include <Leviathan/Math/Leviamath.h>

#include <initializer_list>

#define VEC_3_LENGTH 3

using std::initializer_list;

struct Vec3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		float values[VEC_3_LENGTH];
	};

	DLL Vec3();
	DLL Vec3(float _val);
	DLL Vec3(float _x, float _y, float _z);
	DLL Vec3(initializer_list<float> _values);

	DLL float Magnitude() const;
	DLL float SqrMagnitude() const;
	DLL Vec3 Normalised() const;

	DLL void Normalise();

	DLL static Vec3 Normalise(Vec3 _vec);
	DLL static float Dot(Vec3 _lhs, Vec3 _rhs);
	DLL static Vec3 Cross(Vec3 _lhs, Vec3 _rhs);

};