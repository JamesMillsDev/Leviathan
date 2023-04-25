#include <Leviathan/Math/Vec4.h>

Vec4::Vec4()
    : x(0), y(0), z(0), w(0)
{
}

Vec4::Vec4(const float _val)
    : x(_val), y(_val), z(_val), w(0)
{
}

Vec4::Vec4(const float _x, const float _y, const float _z)
    : x(_x), y(_y), z(_z), w(0)
{
}

Vec4::Vec4(const float _x, const float _y, const float _z, const float _w)
    : x(_x), y(_y), z(_z), w(_w)
{
}

Vec4::Vec4(const initializer_list<float> _values)
    : x(0), y(0), z(0), w(0)
{
    int i = 0;
    for(const float value : _values)
    {
        values[i] = value;
        i++;
    }
}

float Vec4::Magnitude() const
{
    return Leviamath::Sqrt(SqrMagnitude());
}

float Vec4::SqrMagnitude() const
{
    return x * x + y * y + z * z + w * w;
}

Vec4 Vec4::Normalised() const
{
    const float mag = Magnitude();
    Vec4 normal = Vec4(0);

    if(mag != 0)
    {
        normal.x = x / mag;
        normal.y = y / mag;
        normal.z = z / mag;
        normal.w = w / mag;
    }

    return normal;
}

void Vec4::Normalise()
{
    const float mag = Magnitude();

    if(mag != 0)
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

Vec4 Vec4::Normalise(const Vec4 _vec)
{
    const float mag = _vec.Magnitude();
    Vec4 normal = Vec4(0);

    if(mag != 0)
    {
        normal.x = _vec.x / mag;
        normal.y = _vec.y / mag;
        normal.z = _vec.z / mag;
        normal.w = _vec.w / mag;
    }

    return normal;
}

float Vec4::Dot(const Vec4 _lhs, const Vec4 _rhs)
{
    return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z + _lhs.w * _rhs.w;
}
