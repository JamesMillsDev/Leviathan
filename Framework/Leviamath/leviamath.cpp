#include <Leviathan/Math/leviamath.h>

#include <cmath>

const float leviamath::deg2rad = leviamath::pi * 2.f / 360.f;
const float leviamath::rad2deg = 1.f / leviamath::deg2rad;
const float leviamath::pi = 3.14159274f;
const float leviamath::epsilon = 1.401298E-45f;
const float leviamath::positiveInfinity = 1.f / 0.f;
const float leviamath::negativeInfinity = -1.f / 0.f;

float leviamath::min(float _a, float _b)
{
	return fminf(_a, _b);
}

float leviamath::max(float _a, float _b)
{
	return fmaxf(_a, _b);
}

float leviamath::sin(float _theta)
{
	return sinf(_theta);
}

float leviamath::cos(float _theta)
{
	return cosf(_theta);
}

float leviamath::atan2(float _y, float _x)
{
	return atan2f(_y, _x);
}

float leviamath::log(float _val)
{
	return logf(_val);
}

float leviamath::pow(float _val, float _power)
{
	return powf(_val, _power);
}

float leviamath::ceil(float _val)
{
	return ceilf(_val);
}

float leviamath::floor(float _val)
{
	return floorf(_val);
}

float leviamath::sqrt(float _val)
{
	return sqrtf(_val);
}

float leviamath::exp(float _val)
{
	return expf(_val);
}

float leviamath::sign(float _val)
{
	return _val > 0 ? 1 : _val < 0 ? -1 : 0;
}

float leviamath::abs(float _val)
{
	return fabsf(_val);
}

float leviamath::round(float _val)
{
	float whole, fractional;

	fractional = std::modf(_val, &whole);

	return fractional >= 0.5f ? ceil(_val) : floor(_val);
}

int leviamath::roundToInt(float _val)
{
	return static_cast<int>(round(_val));
}

float leviamath::lerp(float _a, float _b, float _t)
{
	_t = clamp01(_t);

	return _a * (1 - _t) + _b * _t;
}

float leviamath::lerpUnclamped(float _a, float _b, float _t)
{
	return _a * (1 - _t) + _b * _t;
}

float leviamath::clamp(float _val, float _min, float _max)
{
	if (_val < _min)
		_val = _min;

	if (_val > _max)
		_val = _max;

	return _val;
}

float leviamath::clamp01(float _val)
{
	if (_val < 0.f)
		return 0.f;

	if (_val > 1.f)
		return 1.f;

	return _val;
}

float leviamath::approximately(float _a, float _b)
{
	return abs(_b - _a) < max(0.000001f * max(abs(_a), abs(_b)), epsilon * 8.f);
}

float leviamath::remap(float _value, float _oldMin, float _oldMax, float _newMin, float _newMax)
{
	return (_value - _oldMin) / (_oldMax - _oldMin) * (_newMax - _newMin) + _newMin;
}
