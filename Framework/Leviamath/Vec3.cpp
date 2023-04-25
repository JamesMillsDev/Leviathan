#include <Leviathan/Math/Vec3.h>

Vec3::Vec3()
    : x(0), y(0), z(0)
{
}

Vec3::Vec3(const float _val)
    : x(_val), y(_val), z(_val)
{
}

Vec3::Vec3(const float _x, const float _y, const float _z)
    : x(_x), y(_y), z(_z)
{
}

Vec3::Vec3(const initializer_list<float> _values)
    : x(0), y(0), z(0)
{
    int i = 0;
    for(const float value : _values)
    {
        values[i] = value;
        i++;
    }
}

float Vec3::Magnitude() const
{
    return Leviamath::Sqrt(SqrMagnitude());
}

float Vec3::SqrMagnitude() const
{
    return x * x + y * y + z * z;
}

Vec3 Vec3::Normalised() const
{
    const float mag = Magnitude();
    Vec3 normal = Vec3(0);

    if(mag != 0)
    {
        normal.x = x / mag;
        normal.y = y / mag;
        normal.z = z / mag;
    }

    return normal;
}

void Vec3::Normalise()
{
    const float mag = Magnitude();

    if(mag != 0)
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

Vec3 Vec3::Normalise(const Vec3 _vec)
{
    const float mag = _vec.Magnitude();
    Vec3 normal = _vec;

    if(mag != 0)
    {
        normal.x = _vec.x / mag;
        normal.y = _vec.y / mag;
        normal.z = _vec.z / mag;
    }

    return normal;
}

float Vec3::Dot(const Vec3 _lhs, const Vec3 _rhs)
{
    return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;
}

Vec3 Vec3::Cross(const Vec3 _lhs, const Vec3 _rhs)
{
    return
    {
        _lhs.y * _rhs.z - _lhs.z * _rhs.y,
        _lhs.z * _rhs.x - _lhs.x * _rhs.z,
        _lhs.x * _rhs.y - _lhs.y * _rhs.x
    };
}
