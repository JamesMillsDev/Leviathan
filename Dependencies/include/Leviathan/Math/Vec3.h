#pragma once

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

	Vec3();
	Vec3(float _val);
	Vec3(float _x, float _y, float _z);
	Vec3(initializer_list<float> _values);

	float Magnitude() const;
	float SqrMagnitude() const;
	Vec3 Normalised() const;

	void Normalise();

	static Vec3 Normalise(Vec3 _vec);
	static float Dot(Vec3 _lhs, Vec3 _rhs);
	static Vec3 Cross(Vec3 _lhs, Vec3 _rhs);

};