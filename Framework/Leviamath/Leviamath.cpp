#include <Leviathan/Math/Leviamath.h>

#include <cmath>

float Leviamath::Min(const float _a, const float _b)
{
	return fminf(_a, _b);
}

float Leviamath::Max(const float _a, const float _b)
{
	return fmaxf(_a, _b);
}

float Leviamath::Sin(const float _theta)
{
	return sinf(_theta);
}

float Leviamath::Cos(const float _theta)
{
	return cosf(_theta);
}

float Leviamath::Atan2(const float _y, const float _x)
{
	return atan2f(_y, _x);
}

float Leviamath::Log(const float _val)
{
	return logf(_val);
}

float Leviamath::Pow(const float _val, const float _power)
{
	return powf(_val, _power);
}

float Leviamath::Ceil(const float _val)
{
	return ceilf(_val);
}

float Leviamath::Floor(const float _val)
{
	return floorf(_val);
}

float Leviamath::Sqrt(const float _val)
{
	return sqrtf(_val);
}

float Leviamath::Exp(const float _val)
{
	return expf(_val);
}

float Leviamath::Sign(const float _val)
{
	return _val > 0.f ? 1.f : _val < 0.f ? -1.f : 0.f;
}

float Leviamath::Abs(const float _val)
{
	return fabsf(_val);
}

float Leviamath::Round(const float _val)
{
	float whole;

	const float fractional = std::modf(_val, &whole);

	return fractional >= 0.5f ? Ceil(_val) : Floor(_val);
}

int Leviamath::RoundToInt(const float _val)
{
	return static_cast<int>(Round(_val));
}

float Leviamath::Lerp(const float _a, const float _b, float _t)
{
	_t = Clamp01(_t);

	return _a * (1 - _t) + _b * _t;
}

float Leviamath::LerpUnclamped(const float _a, const float _b, const float _t)
{
	return _a * (1 - _t) + _b * _t;
}

float Leviamath::Clamp(float _val, const float _min, const float _max)
{
	if (_val < _min)
		_val = _min;

	if (_val > _max)
		_val = _max;

	return _val;
}

float Leviamath::Clamp01(const float _val)
{
	if (_val < 0.f)
		return 0.f;

	if (_val > 1.f)
		return 1.f;

	return _val;
}

float Leviamath::Approximately(const float _a, const float _b)
{
	return Abs(_b - _a) < Max(0.000001f * Max(Abs(_a), Abs(_b)), EPSILON * 8.f);
}

float Leviamath::Remap(const float _value, const float _oldMin, const float _oldMax, const float _newMin, const float _newMax)
{
	return (_value - _oldMin) / (_oldMax - _oldMin) * (_newMax - _newMin) + _newMin;
}
