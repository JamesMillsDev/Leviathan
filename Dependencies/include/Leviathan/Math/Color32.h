#pragma once

#include <cstdint>
#include <raylib/raylib.h>

struct Color32
{
	Color32();
	Color32(uint32_t _val);
	Color32(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha);

	uint8_t Red() const;
	uint8_t Green() const;
	uint8_t Blue() const;
	uint8_t Alpha() const;

	void SetRed(uint8_t _red);
	void SetGreen(uint8_t _green);
	void SetBlue(uint8_t _blue);
	void SetAlpha(uint8_t _alpha);

	operator Color() const;
	operator uint32_t() const;

private:
	uint32_t m_value;

};