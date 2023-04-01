#pragma once

#include <initializer_list>

#define VEC_3_LENGTH 3

using std::initializer_list;

struct vec3
{
public:
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

	vec3();
	vec3(float _val);
	vec3(float _x, float _y, float _z);
	vec3(initializer_list<float> _values);

	float magnitude();
	float sqrMagnitude();
	vec3 normalised();

	void normalise();

	static vec3 normalise(vec3 _vec);
	static float dot(vec3 _lhs, vec3 _rhs);
	static vec3 cross(vec3 _lhs, vec3 _rhs);

};