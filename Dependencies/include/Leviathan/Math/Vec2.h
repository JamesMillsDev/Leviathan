#pragma once

#include <Leviathan/Math/Leviamath.h>

#include <initializer_list>
#include <raylib.h>
#include <Box2D/Common/b2Math.h>

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

	DLL Vec2();
	DLL Vec2(float _val);
	DLL Vec2(float _x, float _y);
	DLL Vec2(initializer_list<float> _values);

	DLL void Set(float _x, float _y);

	DLL float Magnitude() const;
	DLL float SqrMagnitude() const;
	DLL Vec2 Normalised() const;

	DLL void Normalise();

	DLL static float Angle(Vec2 _vec);
	DLL static Vec2 ClampMagnitude(Vec2 _vec, float _maxMag);

	DLL static float Distance(Vec2 _lhs, Vec2 _rhs);
	DLL static float Dot(Vec2 _lhs, Vec2 _rhs);

	DLL static Vec2 Lerp(Vec2 _a, Vec2 _b, float _t);
	DLL static Vec2 LerpUnclamped(Vec2 _a, Vec2 _b, float _t);

	DLL static Vec2 Min(Vec2 _a, Vec2 _b);
	DLL static Vec2 Max(Vec2 _a, Vec2 _b);

	DLL static Vec2 Normalise(Vec2 _vec);

	DLL static Vec2 Reflect(Vec2 _incoming, Vec2 _normal);
	DLL static Vec2 Perpendicular(Vec2 _vec);

	DLL static Vec2 Rotate(Vec2 _vec, float _angle);
	DLL static Vec2 Scale(Vec2 _vec, float _scalar);
	DLL static Vec2 SignedAngle(Vec2 _vec);

	DLL operator Vector2() const;
	DLL operator b2Vec2() const;

};

DLL Vec2 operator+(Vec2 _rhs, Vec2 _lhs);
DLL Vec2 operator-(Vec2 _rhs, Vec2 _lhs);
DLL Vec2 operator*(Vec2 _rhs, float _lhs);
DLL Vec2 operator*(float _rhs, Vec2 _lhs);
DLL Vec2 operator/(Vec2 _rhs, float _lhs);

DLL bool operator==(Vec2 _rhs, Vec2 _lhs);
DLL bool operator!=(Vec2 _rhs, Vec2 _lhs);