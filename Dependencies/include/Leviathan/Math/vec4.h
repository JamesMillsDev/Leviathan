#pragma once

#include <initializer_list>

#define VEC_4_LENGTH 4

using std::initializer_list;

struct vec4
{
public:
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

	vec4();
	vec4(float _val);
	vec4(float _x, float _y, float _z);
	vec4(float _x, float _y, float _z, float _w);
	vec4(initializer_list<float> _values);

	float magnitude();
	float sqrMagnitude();
	vec4 normalised();

	void normalise();

	static vec4 normalise(vec4 _vec);
	static float dot(vec4 _lhs, vec4 _rhs);

};