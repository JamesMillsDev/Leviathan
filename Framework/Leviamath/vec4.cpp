#include <Leviathan/Math/vec4.h>

#include <Leviathan/Math/leviamath.h>

vec4::vec4() : x(0), y(0), z(0), w(0)
{
}

vec4::vec4(float _val) : x(_val), y(_val), z(_val), w(0)
{
}

vec4::vec4(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z), w(0)
{
}

vec4::vec4(float _x, float _y, float _z, float _w) 
	: x(_x), y(_y), z(_z), w(_w)
{
}

vec4::vec4(initializer_list<float> _values) : x(0), y(0), z(0), w(0)
{
	int i = 0;
	for (const float* iter = _values.begin(); iter != _values.end(); iter++)
	{
		values[i] = *iter;
		i++;
	}
}

float vec4::magnitude()
{
	return leviamath::sqrt(sqrMagnitude());
}

float vec4::sqrMagnitude()
{
	return x * x + y * y + z * z + w * w;
}

vec4 vec4::normalised()
{
	float mag = magnitude();
	vec4 normal = vec4(0);

	if (mag != 0)
	{
		normal.x = x / mag;
		normal.y = y / mag;
		normal.z = z / mag;
		normal.w = w / mag;
	}

	return normal;
}

void vec4::normalise()
{
	float mag = magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
	else
	{
		x = y = z = w = 0;
	}
}

vec4 vec4::normalise(vec4 _vec)
{
	float mag = _vec.magnitude();
	vec4 normal = vec4(0);

	if (mag != 0)
	{
		normal.x = _vec.x / mag;
		normal.y = _vec.y / mag;
		normal.z = _vec.z / mag;
		normal.w = _vec.w / mag;
	}

	return normal;
}

float vec4::dot(vec4 _lhs, vec4 _rhs)
{
	return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z + _lhs.w * _rhs.w;
}
