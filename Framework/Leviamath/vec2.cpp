#include <Leviathan/Math/vec2.h>

#include <Leviathan/Math/leviamath.h>

vec2::vec2() : x(0), y(0)
{
}

vec2::vec2(float _val) : x(_val), y(_val)
{
}

vec2::vec2(float _x, float _y) : x(_x), y(_y)
{
}

vec2::vec2(initializer_list<float> _values) : x(0), y(0)
{
	for (const float* iter = _values.begin(), int i = 0; iter != _values.end(); iter++, i++)
	{
		values[i] = *iter;
	}
}

void vec2::set(float _x, float _y)
{
	x = _x;
	y = _y;
}

float vec2::magnitude()
{
	return leviamath::sqrt(sqrMagnitude());
}

float vec2::sqrMagnitude()
{
	return x * x + y * y;
}

vec2 vec2::normalised()
{
	float mag = magnitude();
	vec2 normal = vec2(0);

	if (mag != 0)
	{
		normal.x = x / mag;
		normal.y = y / mag;
	}

	return normal;
}

void vec2::normalise()
{
	float mag = magnitude();

	if (mag != 0)
	{
		x /= mag;
		y /= mag;
	}
	else
	{
		x = y = 0;
	}
}

float vec2::angle(vec2 _vec)
{
	return leviamath::atan2(_vec.y, _vec.x);
}

vec2 vec2::clampMagnitude(vec2 _vec, float _maxMag)
{
	if (_vec.magnitude() <= _maxMag)
		return _vec;

	_vec.normalise();
	return _vec * _maxMag;
}

float vec2::distance(vec2 _lhs, vec2 _rhs)
{
	return (_lhs - _rhs).magnitude();
}

float vec2::dot(vec2 _lhs, vec2 _rhs)
{
	return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
}

vec2 vec2::lerp(vec2 _a, vec2 _b, float _t)
{
	_t = leviamath::clamp01(_t);

	return _a * (1 - _t) + _b * _t;
}

vec2 vec2::lerpUnclamped(vec2 _a, vec2 _b, float _t)
{
	return _a * (1 - _t) + _b * _t;
}

vec2 vec2::min(vec2 _a, vec2 _b)
{
	return vec2(leviamath::min(_a.x, _b.x), leviamath::min(_a.y, _b.y));
}

vec2 vec2::max(vec2 _a, vec2 _b)
{
	return vec2(leviamath::max(_a.x, _b.x), leviamath::max(_a.y, _b.y));
}

vec2 vec2::normalise(vec2 _vec)
{
	float mag = _vec.magnitude();
	vec2 normal = _vec;

	if (mag != 0)
	{
		normal.x = _vec.x / mag;
		normal.y = _vec.y / mag;
	}

	return normal;
}

vec2 vec2::reflect(vec2 _incoming, vec2 _normal)
{
	float dot = vec2::dot(_incoming, _normal);

	return _incoming - (2 * dot * _normal);
}

vec2 vec2::perpendicular(vec2 _vec)
{
	return vec2(-_vec.y, _vec.x);
}

vec2 vec2::rotate(vec2 _vec, float _angle)
{
	float angle = _angle * leviamath::deg2rad;

	return 
	{
		_vec.x * leviamath::cos(angle) - _vec.y * leviamath::sin(angle),
		_vec.y * leviamath::sin(angle) + _vec.y * leviamath::cos(angle)
	};
}

vec2 vec2::scale(vec2 _vec, float _scalar)
{
	return _vec * _scalar;
}

vec2 vec2::signedAngle(vec2 _vec)
{
	return leviamath::atan2(_vec.y, _vec.x) - 180.f;
}

vec2::operator Vector2()
{
	return { x, y };
}

vec2 operator+(vec2 _rhs, vec2 _lhs)
{
	return { _rhs.x + _lhs.x, _rhs.y + _lhs.y };
}

vec2 operator-(vec2 _rhs, vec2 _lhs)
{
	return { _rhs.x - _lhs.x, _rhs.y - _lhs.y };
}

vec2 operator*(vec2 _rhs, float _lhs)
{
	return { _rhs.x * _lhs, _rhs.y * _lhs };
}

vec2 operator*(float _rhs, vec2 _lhs)
{
	return { _rhs * _lhs.x, _rhs * _lhs.y };
}

vec2 operator/(vec2 _rhs, float _lhs)
{
	return { _rhs.x / _lhs, _rhs.y / _lhs };
}

bool operator==(vec2 _rhs, vec2 _lhs)
{
	return leviamath::approximately(_rhs.x, _lhs.x) && leviamath::approximately(_rhs.y, _lhs.y);
}

bool operator!=(vec2 _rhs, vec2 _lhs)
{
	return !(_rhs == _lhs);
}
