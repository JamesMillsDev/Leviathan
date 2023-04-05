#pragma once

#include <initializer_list>

#define MAT_3_LENGTH 3
#define MAT_3_SIZE (MAT_3_LENGTH * MAT_3_LENGTH)

using std::initializer_list;

struct mat3
{
	union
	{
		struct
		{
			float m1, m2, m3, m4, m5, m6, m7, m8, m9;
		};

		float values[MAT_3_SIZE];
	};

	mat3();
	mat3(float _values);
	mat3(float _m1, float _m4, float _m7, float _m2, float _m5, float _m8, float _m3, float _m6, float _m9);
	mat3(initializer_list<float> _values);

	struct vec2 transformPoint(vec2 _point);
	struct vec2 transformVector(vec2 _vec);

	void setXRotation(float _theta);
	void setYRotation(float _theta);
	void setZRotation(float _theta);

	float getXRotation();
	float getYRotation();
	float getZRotation();

	void setTranslation(float _x, float _y);
	void setTranslation(struct vec2 _translation);

	void translate(float _x, float _y);
	void translate(struct vec2 _translation);

	void getTranslation(float& _x, float& _y);
	struct vec2 getTranslation();

	void setScale(float _x, float _y);
	void setScale(struct vec2 _scale);

	void getScale(float& _x, float& _y);
	struct vec2 getScale();

	struct vec3 getXAxis();
	struct vec3 getYAxis();
	struct vec3 getZAxis();

	static mat3 identity();

};

static mat3 operator*(mat3 _lhs, mat3 _rhs);
static mat3 operator*(mat3 _lhs, struct vec3 _rhs);
static mat3 operator*(struct vec3 _lhs, mat3 _rhs);