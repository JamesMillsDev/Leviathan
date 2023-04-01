#pragma once

#include <initializer_list>
#include <raylib/raymath.h>

#define VEC_2_LENGTH 2

using std::initializer_list;

struct vec2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};

		float values[VEC_2_LENGTH];
	};

	vec2();
	vec2(float _val);
	vec2(float _x, float _y);
	vec2(initializer_list<float> _values);

	void set(float _x, float _y);

	float magnitude();
	float sqrMagnitude();
	vec2 normalised();

	void normalise();

	static float angle(vec2 _vec);
	static vec2 clampMagnitude(vec2 _vec, float _maxMag);

	static float distance(vec2 _lhs, vec2 _rhs);
	static float dot(vec2 _lhs, vec2 _rhs);

	static vec2 lerp(vec2 _a, vec2 _b, float _t);
	static vec2 lerpUnclamped(vec2 _a, vec2 _b, float _t);

	static vec2 min(vec2 _a, vec2 _b);
	static vec2 max(vec2 _a, vec2 _b);

	static vec2 normalise(vec2 _vec);

	static vec2 reflect(vec2 _incoming, vec2 _normal);
	static vec2 perpendicular(vec2 _vec);

	static vec2 rotate(vec2 _vec, float _angle);
	static vec2 scale(vec2 _vec, float _scalar);
	static vec2 signedAngle(vec2 _vec);

	operator Vector2();

};

vec2 operator+(vec2 _rhs, vec2 _lhs);
vec2 operator-(vec2 _rhs, vec2 _lhs);
vec2 operator*(vec2 _rhs, float _lhs);
vec2 operator*(float _rhs, vec2 _lhs);
vec2 operator/(vec2 _rhs, float _lhs);

bool operator==(vec2 _rhs, vec2 _lhs);
bool operator!=(vec2 _rhs, vec2 _lhs);