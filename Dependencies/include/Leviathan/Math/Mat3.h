#pragma once

#include <Leviathan/Math/Leviamath.h>

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

	DLL Mat3();
	DLL Mat3(float _values);
	DLL Mat3(float _m1, float _m4, float _m7, float _m2, float _m5, float _m8, float _m3, float _m6, float _m9);
	DLL Mat3(initializer_list<float> _values);

	DLL struct Vec2 TransformPoint(Vec2 _point) const;
	DLL struct Vec2 TransformVector(Vec2 _vec) const;

	DLL void SetRotation(float _theta);

	DLL float GetRotation() const;

	DLL void SetTranslation(float _x, float _y);
	DLL void SetTranslation(struct Vec2 _translation);

	DLL void Translate(float _x, float _y);
	DLL void Translate(struct Vec2 _translation);

	DLL void GetTranslation(float& _x, float& _y) const;
	DLL struct Vec2 GetTranslation();

	DLL void SetScale(float _x, float _y);
	DLL void SetScale(struct Vec2 _scale);

	DLL void GetScale(float& _x, float& _y);
	DLL struct Vec2 GetScale();

	DLL struct Vec3 GetXAxis();
	DLL struct Vec3 GetYAxis();
	DLL struct Vec3 GetZAxis();

	DLL static Mat3 Identity();

};

DLL extern Mat3 operator*(Mat3 _lhs, Mat3 _rhs);
DLL extern Vec3 operator*(Mat3 _lhs, struct Vec3 _rhs);
DLL extern Vec3 operator*(struct Vec3 _lhs, Mat3 _rhs);