#include <Leviathan/Core/Color32.h>

namespace Leviathan
{
    Color32::Color32() : m_value(0xffffffff)
    {
    }

    Color32::Color32(const uint32_t _val)
        : m_value(_val)
    {
    }

    Color32::Color32(const uint8_t _red, const uint8_t _green, const uint8_t _blue, const uint8_t _alpha)
        : m_value(0x00000000)
    {
        SetRed(_red);
        SetGreen(_green);
        SetBlue(_blue);
        SetAlpha(_alpha);
    }

    uint8_t Color32::Red() const
    {
        return (uint8_t)(m_value >> 24 & 0xff);
    }

    uint8_t Color32::Green() const
    {
        return (uint8_t)(m_value >> 16 & 0xff);
    }

    uint8_t Color32::Blue() const
    {
        return (uint8_t)(m_value >> 8 & 0xff);
    }

    uint8_t Color32::Alpha() const
    {
        return (uint8_t)(m_value >> 0 & 0xff);
    }

    void Color32::SetRed(const uint8_t _red)
    {
        m_value = (m_value & 0x00ffffff) | ((uint32_t)_red << 24);
    }

    void Color32::SetGreen(const uint8_t _green)
    {
        m_value = (m_value & 0xff00ffff) | ((uint32_t)_green << 16);
    }

    void Color32::SetBlue(const uint8_t _blue)
    {
        m_value = (m_value & 0xffff00ff) | ((uint32_t)_blue << 8);
    }

    void Color32::SetAlpha(const uint8_t _alpha)
    {
        m_value = (m_value & 0xffffff00) | ((uint32_t)_alpha << 0);
    }

    Color32::operator Color() const
    {
        Color color;
        color.r = Red();
        color.g = Green();
        color.b = Blue();
        color.a = Alpha();

        return color;
    }

    Color32::operator uint32_t() const
    {
        return m_value;
    }
}