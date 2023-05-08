#include <Leviathan/Math/Vec2.h>

Vec2::Vec2() : x(0), y(0)
{
}

Vec2::Vec2(const float _val) : x(_val), y(_val)
{
}

Vec2::Vec2(const float _x, const float _y) : x(_x), y(_y)
{
}

Vec2::Vec2(const initializer_list<float> _values)
    : x(0), y(0)
{
    int i = 0;
    for(const float value : _values)
    {
        values[i] = value;
        i++;
    }
}

void Vec2::Set(const float _x, const float _y)
{
    x = _x;
    y = _y;
}

float Vec2::Magnitude() const
{
    return Leviamath::Sqrt(SqrMagnitude());
}

float Vec2::SqrMagnitude() const
{
    return x * x + y * y;
}

Vec2 Vec2::Normalised() const
{
    const float mag = Magnitude();
    Vec2 normal = Vec2(0);

    if(mag != 0)
    {
        normal.x = x / mag;
        normal.y = y / mag;
    }

    return normal;
}

void Vec2::Normalise()
{
    const float mag = Magnitude();

    if(mag != 0)
    {
        x /= mag;
        y /= mag;
    }
    else
    {
        x = y = 0;
    }
}

float Vec2::Angle(const Vec2 _vec)
{
    return Leviamath::Atan2(_vec.y, _vec.x);
}

Vec2 Vec2::ClampMagnitude(Vec2 _vec, const float _maxMag)
{
    if(_vec.Magnitude() <= _maxMag)
        return _vec;

    _vec.Normalise();
    return _vec * _maxMag;
}

float Vec2::Distance(const Vec2 _lhs, const Vec2 _rhs)
{
    return (_lhs - _rhs).Magnitude();
}

float Vec2::Dot(const Vec2 _lhs, const Vec2 _rhs)
{
    return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
}

Vec2 Vec2::Lerp(const Vec2 _a, const Vec2 _b, float _t)
{
    _t = Leviamath::Clamp01(_t);

    return _a * (1 - _t) + _b * _t;
}

Vec2 Vec2::LerpUnclamped(const Vec2 _a, const Vec2 _b, const float _t)
{
    return _a * (1 - _t) + _b * _t;
}

Vec2 Vec2::Min(const Vec2 _a, const Vec2 _b)
{
    return { Leviamath::Min(_a.x, _b.x), Leviamath::Min(_a.y, _b.y) };
}

Vec2 Vec2::Max(const Vec2 _a, const Vec2 _b)
{
    return { Leviamath::Max(_a.x, _b.x), Leviamath::Max(_a.y, _b.y) };
}

Vec2 Vec2::Normalise(const Vec2 _vec)
{
    const float mag = _vec.Magnitude();
    Vec2 normal = _vec;

    if(mag != 0)
    {
        normal.x = _vec.x / mag;
        normal.y = _vec.y / mag;
    }

    return normal;
}

Vec2 Vec2::Reflect(const Vec2 _incoming, const Vec2 _normal)
{
    const float dot = Dot(_incoming, _normal);

    return _incoming - 2 * dot * _normal;
}

Vec2 Vec2::Perpendicular(const Vec2 _vec)
{
    return { -_vec.y, _vec.x };
}

Vec2 Vec2::Rotate(const Vec2 _vec, const float _angle)
{
    const float angle = _angle * DEG_2_RAD;

    return
    {
        _vec.x * Leviamath::Cos(angle) - _vec.y * Leviamath::Sin(angle),
        _vec.y * Leviamath::Sin(angle) + _vec.y * Leviamath::Cos(angle)
    };
}

Vec2 Vec2::Scale(const Vec2 _vec, const float _scalar)
{
    return _vec * _scalar;
}

Vec2 Vec2::SignedAngle(const Vec2 _vec)
{
    return Leviamath::Atan2(_vec.y, _vec.x) - 180.f;
}

Vec2::operator Vector2() const
{
    return { x, y };
}

Vec2::operator b2Vec2() const
{
    return { x, y };
}

Vec2 operator+(const Vec2 _rhs, const Vec2 _lhs)
{
    return { _rhs.x + _lhs.x, _rhs.y + _lhs.y };
}

Vec2 operator-(const Vec2 _rhs, const Vec2 _lhs)
{
    return { _rhs.x - _lhs.x, _rhs.y - _lhs.y };
}

Vec2 operator*(const Vec2 _rhs, const float _lhs)
{
    return { _rhs.x * _lhs, _rhs.y * _lhs };
}

Vec2 operator*(const float _rhs, const Vec2 _lhs)
{
    return { _rhs * _lhs.x, _rhs * _lhs.y };
}

Vec2 operator/(const Vec2 _rhs, const float _lhs)
{
    return { _rhs.x / _lhs, _rhs.y / _lhs };
}

bool operator==(const Vec2 _rhs, const Vec2 _lhs)
{
    return Leviamath::Approximately(_rhs.x, _lhs.x) && Leviamath::Approximately(_rhs.y, _lhs.y);  // NOLINT(clang-diagnostic-float-conversion)
}

bool operator!=(const Vec2 _rhs, const Vec2 _lhs)
{
    return !(_rhs == _lhs);
}
