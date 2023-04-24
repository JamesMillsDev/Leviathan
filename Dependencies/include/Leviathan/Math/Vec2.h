#pragma once

#include <initializer_list>
#include <raylib/raylib.h>

#define VEC_2_LENGTH 2

using std::initializer_list;

struct Vec2
{
	union
	{
		struct
		{
			float x;
			float y;
		};

		float values[VEC_2_LENGTH];
	};

	Vec2();
	Vec2(float _val);
	Vec2(float _x, float _y);
	Vec2(initializer_list<float> _values);

	void Set(float _x, float _y);

	float Magnitude() const;
	float SqrMagnitude() const;
	Vec2 Normalised() const;

	void Normalise();

	static float Angle(Vec2 _vec);
	static Vec2 ClampMagnitude(Vec2 _vec, float _maxMag);

	static float Distance(Vec2 _lhs, Vec2 _rhs);
	static float Dot(Vec2 _lhs, Vec2 _rhs);

	static Vec2 Lerp(Vec2 _a, Vec2 _b, float _t);
	static Vec2 LerpUnclamped(Vec2 _a, Vec2 _b, float _t);

	static Vec2 Min(Vec2 _a, Vec2 _b);
	static Vec2 Max(Vec2 _a, Vec2 _b);

	static Vec2 Normalise(Vec2 _vec);

	static Vec2 Reflect(Vec2 _incoming, Vec2 _normal);
	static Vec2 Perpendicular(Vec2 _vec);

	static Vec2 Rotate(Vec2 _vec, float _angle);
	static Vec2 Scale(Vec2 _vec, float _scalar);
	static Vec2 SignedAngle(Vec2 _vec);

	operator Vector2() const;

};

Vec2 operator+(Vec2 _rhs, Vec2 _lhs);
Vec2 operator-(Vec2 _rhs, Vec2 _lhs);
Vec2 operator*(Vec2 _rhs, float _lhs);
Vec2 operator*(float _rhs, Vec2 _lhs);
Vec2 operator/(Vec2 _rhs, float _lhs);

bool operator==(Vec2 _rhs, Vec2 _lhs);
bool operator!=(Vec2 _rhs, Vec2 _lhs);