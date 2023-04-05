#include <Leviathan/Math/vec3.h>

#include <Leviathan/Math/leviamath.h>

vec3::vec3() : x(0), y(0), z(0)
{
}

vec3::vec3(float _val) : x(_val), y(_val), z(_val)
{
}

vec3::vec3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

vec3::vec3(initializer_list<float> _values) : x(0), y(0), z(0)
{
	int i = 0;
	for (const float* iter = _values.begin(); iter != _values.end(); iter++)
	{
		values[i] = *iter;
		i++;
	}
}

float vec3::magnitude()
{
	return leviamath::sqrt(sqrMagnitude());
}

float vec3::sqrMagnitude()
{
	return x * x + y * y + z * z;
}

vec3 vec3::normalised()
{
	float mag = magnitude();
	vec3 normal = vec3(0);

	if (mag != 0)
	{
		normal.x = x / mag;
		normal.y = y / mag;
		normal.z = z / mag;
	}

	return normal;
}

void vec3::normalise()
{
	float mag = magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
	else
	{
		x = y = z = 0;
	}
}

vec3 vec3::normalise(vec3 _vec)
{
	float mag = _vec.magnitude();
	vec3 normal = _vec;

	if (mag != 0)
	{
		normal.x = _vec.x / mag;
		normal.y = _vec.y / mag;
		normal.z = _vec.z / mag;
	}

	return normal;
}

float vec3::dot(vec3 _lhs, vec3 _rhs)
{
	return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;
}

vec3 vec3::cross(vec3 _lhs, vec3 _rhs)
{
	return vec3(
		_lhs.y * _rhs.z - _lhs.z * _rhs.y,
		_lhs.z * _rhs.x - _lhs.x * _rhs.z,
		_lhs.x * _rhs.y - _lhs.y * _rhs.x);
}
