#include <Leviathan/Math/color.h>

color::color() : m_value(0xffffffff)
{
}

color::color(uint32_t _val) : m_value(_val)
{
}

color::color(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha) : m_value(0x00000000)
{
	setRed(_red);
	setGreen(_green);
	setBlue(_blue);
	setAlpha(_alpha);
}

uint8_t color::red()
{
	return (uint8_t)((m_value >> 24) & 0xff);
}

uint8_t color::green()
{
	return (uint8_t)((m_value >> 16) & 0xff);
}

uint8_t color::blue()
{
	return (uint8_t)((m_value >> 8) & 0xff);
}

uint8_t color::alpha()
{
	return (uint8_t)((m_value >> 0) & 0xff);
}

void color::setRed(uint8_t _red)
{
	m_value = (m_value & 0x00ffffff) | ((uint32_t)_red << 24);
}

void color::setGreen(uint8_t _green)
{
	m_value = (m_value & 0xff00ffff) | ((uint32_t)_green << 16);
}

void color::setBlue(uint8_t _blue)
{
	m_value = (m_value & 0xffff00ff) | ((uint32_t)_blue << 8);
}

void color::setAlpha(uint8_t _alpha)
{
	m_value = (m_value & 0xffffff00) | ((uint32_t)_alpha << 0);
}

color::operator Color()
{
	Color color;
	color.r = (unsigned char)red();
	color.g = (unsigned char)green();
	color.b = (unsigned char)blue();
	color.a = (unsigned char)alpha();

	return color;
}

color::operator uint32_t()
{
	return m_value;
}
