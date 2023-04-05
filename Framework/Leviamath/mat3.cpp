#include <Leviathan/Math/mat3.h>

#include <Leviathan/Math/leviamath.h>

#include <Leviathan/Math/vec2.h>
#include <Leviathan/Math/vec3.h>

mat3::mat3() :
	m1(1), m4(0), m7(0),
	m2(1), m5(1), m8(0),
	m3(0), m6(0), m9(1)
{
}

mat3::mat3(float _values) :
	m1(_values), m4(_values), m7(_values),
	m2(_values), m5(_values), m8(_values),
	m3(_values), m6(_values), m9(_values)
{
}

mat3::mat3(float _m1, float _m4, float _m7, float _m2, float _m5, float _m8, float _m3, float _m6, float _m9) :
	m1(_m1), m4(_m4), m7(_m7),
	m2(_m2), m5(_m5), m8(_m8),
	m3(_m3), m6(_m6), m9(_m9)
{
}

mat3::mat3(initializer_list<float> _values) :
	m1(1), m4(0), m7(0),
	m2(1), m5(1), m8(0),
	m3(0), m6(0), m9(1)
{
	int i = 0;
	for (const float* iter = _values.begin(); iter != _values.end(); iter++)
	{
		values[i] = *iter;
		i++;
	}
}

vec2 mat3::transformPoint(vec2 _point)
{
	return
	{
		_point.x * m1 + _point.y * m4 + m7,
		_point.x * m2 + _point.y * m5 + m8
	};
}

vec2 mat3::transformVector(vec2 _vec)
{
	return
	{
		_vec.x * m1 + _vec.y * m4,
		_vec.x * m2 + _vec.y * m5
	};
}

void mat3::setXRotation(float _theta)
{
	float yLen = getYAxis().magnitude();
	float zLen = getZAxis().magnitude();

	float cos = leviamath::cos(_theta);
	float sin = leviamath::sin(_theta);

	m5 = cos * yLen;
	m8 = -sin * zLen;
	m6 = sin * yLen;
	m9 = cos * zLen;
}

void mat3::setYRotation(float _theta)
{
	float xLen = getXAxis().magnitude();
	float zLen = getZAxis().magnitude();

	float cos = leviamath::cos(_theta);
	float sin = leviamath::sin(_theta);

	m1 = cos * xLen;
	m7 = sin * zLen;
	m3 = -sin * xLen;
	m9 = cos * zLen;
}

void mat3::setZRotation(float _theta)
{
	float xLen = getXAxis().magnitude();
	float yLen = getYAxis().magnitude();

	float cos = leviamath::cos(_theta);
	float sin = leviamath::sin(_theta);

	m1 = cos * xLen;
	m4 = -sin * yLen;
	m2 = sin * xLen;
	m5 = cos * yLen;
}

float mat3::getXRotation()
{
	return leviamath::atan2(m2, m1);
}

float mat3::getYRotation()
{
	return leviamath::atan2(-m4, m5);
}

float mat3::getZRotation()
{
	return leviamath::atan2(m7, m9);
}

void mat3::setTranslation(float _x, float _y)
{
	setTranslation({ _x, _y });
}

void mat3::setTranslation(vec2 _translation)
{
	m7 = _translation.x;
	m8 = _translation.y;
}

void mat3::translate(float _x, float _y)
{
	translate({ _x, _y });
}

void mat3::translate(vec2 _translation)
{
	m7 += _translation.x;
	m8 += _translation.y;
}

void mat3::getTranslation(float& _x, float& _y)
{
	_x = m7;
	_y = m8;
}

vec2 mat3::getTranslation()
{
	return { m7, m8 };
}

void mat3::setScale(float _x, float _y)
{
	setScale({ _x, _y });
}

void mat3::setScale(vec2 _scale)
{
	float xLen = getXAxis().magnitude();
	float yLen = getYAxis().magnitude();

	if (xLen > 0)
	{
		m1 = (m1 / xLen) * _scale.x;
		m2 = (m2 / xLen) * _scale.x;
		m3 = (m3 / xLen) * _scale.x;
	}

	if (yLen > 0)
	{
		m4 = (m4 / yLen) * _scale.y;
		m5 = (m5 / yLen) * _scale.y;
		m6 = (m6 / yLen) * _scale.y;
	}
}

void mat3::getScale(float& _x, float& _y)
{
	_x = getXAxis().magnitude();
	_y = getYAxis().magnitude();
}

vec2 mat3::getScale()
{
	return
	{
		getXAxis().magnitude(),
		getYAxis().magnitude()
	};
}

vec3 mat3::getXAxis()
{
	return { m1, m2, m3 };
}

vec3 mat3::getYAxis()
{
	return { m4, m5, m6 };
}

vec3 mat3::getZAxis()
{
	return { m7, m8, m9 };
}

mat3 mat3::identity()
{
	return mat3();
}

mat3 operator*(mat3 _lhs, mat3 _rhs)
{
	return
	{
		_lhs.m1 * _rhs.m1 + _lhs.m2 * _rhs.m4 + _lhs.m3 * _rhs.m7,
		_lhs.m4 * _rhs.m1 + _lhs.m5 * _rhs.m4 + _lhs.m6 * _rhs.m7,
		_lhs.m7 * _rhs.m1 + _lhs.m8 * _rhs.m4 + _lhs.m9 * _rhs.m7,
		_lhs.m1 * _rhs.m2 + _lhs.m2 * _rhs.m5 + _lhs.m3 * _rhs.m8,
		_lhs.m4 * _rhs.m2 + _lhs.m5 * _rhs.m5 + _lhs.m6 * _rhs.m8,
		_lhs.m7 * _rhs.m2 + _lhs.m8 * _rhs.m5 + _lhs.m9 * _rhs.m8,
		_lhs.m1 * _rhs.m3 + _lhs.m2 * _rhs.m6 + _lhs.m3 * _rhs.m9,
		_lhs.m4 * _rhs.m3 + _lhs.m5 * _rhs.m6 + _lhs.m6 * _rhs.m9,
		_lhs.m7 * _rhs.m3 + _lhs.m8 * _rhs.m6 + _lhs.m9 * _rhs.m9
	};
}

mat3 operator*(mat3 _lhs, vec3 _rhs)
{
	return
	{
		_lhs.m1 * _rhs.x + _lhs.m2 * _rhs.y + _lhs.m3 * _rhs.z,
		_lhs.m4 * _rhs.x + _lhs.m5 * _rhs.y + _lhs.m6 * _rhs.z,
		_lhs.m7 * _rhs.x + _lhs.m8 * _rhs.y + _lhs.m9 * _rhs.z
	};
}

mat3 operator*(vec3 _lhs, mat3 _rhs)
{
	return
	{
		_lhs.x* _rhs.m1 + _lhs.y * _rhs.m4 + _lhs.z * _rhs.m7,
		_lhs.x* _rhs.m2 + _lhs.y * _rhs.m5 + _lhs.z * _rhs.m8,
		_lhs.x* _rhs.m3 + _lhs.y * _rhs.m6 + _lhs.z * _rhs.m9
	};
}
