#pragma once

#include <cstdint>
#include <raylib/raylib.h>

struct color
{
public:
	color();
	color(uint32_t _val);
	color(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha);

	uint8_t red();
	uint8_t green();
	uint8_t blue();
	uint8_t alpha();

	void setRed(uint8_t _red);
	void setGreen(uint8_t _green);
	void setBlue(uint8_t _blue);
	void setAlpha(uint8_t _alpha);

	operator Color();
	operator uint32_t();

private:
	uint32_t m_value;

};