#pragma once

#include <initializer_list>

#define MAT_3_LENGTH 3
#define MAT_3_SIZE (MAT_3_LENGTH * MAT_3_LENGTH)

using std::initializer_list;

struct Mat3
{
	union
	{
		struct
		{
			float m1, m2, m3, m4, m5, m6, m7, m8, m9;
		};

		float values[MAT_3_SIZE];
	};

	Mat3();
	Mat3(float _values);
	Mat3(float _m1, float _m4, float _m7, float _m2, float _m5, float _m8, float _m3, float _m6, float _m9);
	Mat3(initializer_list<float> _values);

	struct Vec2 TransformPoint(Vec2 _point) const;
	struct Vec2 TransformVector(Vec2 _vec) const;

	void SetRotation(float _theta);

	float GetRotation() const;

	void SetTranslation(float _x, float _y);
	void SetTranslation(struct Vec2 _translation);

	void Translate(float _x, float _y);
	void Translate(struct Vec2 _translation);

	void GetTranslation(float& _x, float& _y) const;
	struct Vec2 GetTranslation();

	void SetScale(float _x, float _y);
	void SetScale(struct Vec2 _scale);

	void GetScale(float& _x, float& _y);
	struct Vec2 GetScale();

	struct Vec3 GetXAxis();
	struct Vec3 GetYAxis();
	struct Vec3 GetZAxis();

	static Mat3 Identity();

};

static Mat3 operator*(Mat3 _lhs, Mat3 _rhs);
static Vec3 operator*(Mat3 _lhs, struct Vec3 _rhs);
static Vec3 operator*(struct Vec3 _lhs, Mat3 _rhs);