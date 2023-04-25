#include <Leviathan/Math/Mat3.h>

#include <Leviathan/Math/Vec2.h>
#include <Leviathan/Math/Vec3.h>

Mat3::Mat3() :
    m1(1), m2(1), m3(0),
    m4(0), m5(1), m6(0),
    m7(0), m8(0), m9(1)
{
}

Mat3::Mat3(const float _values) :
    m1(_values), m2(_values), m3(_values),
    m4(_values), m5(_values), m6(_values),
    m7(_values), m8(_values), m9(_values)
{
}

Mat3::Mat3(const float _m1, const float _m4, const float _m7, const float _m2, const float _m5, const float _m8, const float _m3, const float _m6, const float _m9) :
    m1(_m1), m2(_m2), m3(_m3),
    m4(_m4), m5(_m5), m6(_m6),
    m7(_m7), m8(_m8), m9(_m9)
{
}

Mat3::Mat3(const initializer_list<float> _values) :
    m1(1), m2(1), m3(0),
    m4(0), m5(1), m6(0),
    m7(0), m8(0), m9(1)
{
    int i = 0;
    for(const float& value : _values)
    {
        values[i] = value;
        i++;
    }
}

Vec2 Mat3::TransformPoint(const Vec2 _point) const
{
    return
    {
        _point.x * m1 + _point.y * m4 + m7,
        _point.x * m2 + _point.y * m5 + m8
    };
}

Vec2 Mat3::TransformVector(const Vec2 _vec) const
{
    return
    {
        _vec.x * m1 + _vec.y * m4,
        _vec.x * m2 + _vec.y * m5
    };
}

void Mat3::SetRotation(const float _theta)
{
    const float xLen = GetXAxis().Magnitude();
    const float yLen = GetYAxis().Magnitude();

    const float cos = Leviamath::Cos(_theta);
    const float sin = Leviamath::Sin(_theta);

    m1 = cos * xLen;
    m4 = -sin * yLen;
    m2 = sin * xLen;
    m5 = cos * yLen;
}

float Mat3::GetRotation() const
{
    return Leviamath::Atan2(m2, m1);
}

void Mat3::SetTranslation(float _x, float _y)
{
    SetTranslation({ _x, _y });
}

void Mat3::SetTranslation(const Vec2 _translation)
{
    m7 = _translation.x;
    m8 = _translation.y;
}

void Mat3::Translate(float _x, float _y)
{
    Translate({ _x, _y });
}

void Mat3::Translate(const Vec2 _translation)
{
    m7 += _translation.x;
    m8 += _translation.y;
}

void Mat3::GetTranslation(float& _x, float& _y) const
{
    _x = m7;
    _y = m8;
}

Vec2 Mat3::GetTranslation()
{
    return { m7, m8 };
}

void Mat3::SetScale(float _x, float _y)
{
    SetScale({ _x, _y });
}

void Mat3::SetScale(const Vec2 _scale)
{
    const float xLen = GetXAxis().Magnitude();
    const float yLen = GetYAxis().Magnitude();

    if(xLen > 0)
    {
        m1 = (m1 / xLen) * _scale.x;
        m2 = (m2 / xLen) * _scale.x;
        m3 = (m3 / xLen) * _scale.x;
    }

    if(yLen > 0)
    {
        m4 = (m4 / yLen) * _scale.y;
        m5 = (m5 / yLen) * _scale.y;
        m6 = (m6 / yLen) * _scale.y;
    }
}

void Mat3::GetScale(float& _x, float& _y)
{
    _x = GetXAxis().Magnitude();
    _y = GetYAxis().Magnitude();
}

Vec2 Mat3::GetScale()
{
    return
    {
        GetXAxis().Magnitude(),
        GetYAxis().Magnitude()
    };
}

Vec3 Mat3::GetXAxis()
{
    return { m1, m2, m3 };
}

Vec3 Mat3::GetYAxis()
{
    return { m4, m5, m6 };
}

Vec3 Mat3::GetZAxis()
{
    return { m7, m8, m9 };
}

Mat3 Mat3::Identity()
{
    return
    {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
}

Mat3 operator*(const Mat3 _lhs, const Mat3 _rhs)
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

Vec3 operator*(const Mat3 _lhs, const Vec3 _rhs)
{
    return
    {
        _lhs.m1 * _rhs.x + _lhs.m2 * _rhs.y + _lhs.m3 * _rhs.z,
        _lhs.m4 * _rhs.x + _lhs.m5 * _rhs.y + _lhs.m6 * _rhs.z,
        _lhs.m7 * _rhs.x + _lhs.m8 * _rhs.y + _lhs.m9 * _rhs.z
    };
}

Vec3 operator*(const Vec3 _lhs, const Mat3 _rhs)
{
    return
    {
        _lhs.x * _rhs.m1 + _lhs.y * _rhs.m4 + _lhs.z * _rhs.m7,
        _lhs.x * _rhs.m2 + _lhs.y * _rhs.m5 + _lhs.z * _rhs.m8,
        _lhs.x * _rhs.m3 + _lhs.y * _rhs.m6 + _lhs.z * _rhs.m9
    };
}
