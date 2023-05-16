#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <cstdint>
#include <raylib.h>

struct Color32
{
public:
	DLL Color32();
	DLL Color32(uint32_t _val);
	DLL Color32(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha);

	DLL uint8_t Red() const;
	DLL uint8_t Green() const;
	DLL uint8_t Blue() const;
	DLL uint8_t Alpha() const;

	DLL void SetRed(uint8_t _red);
	DLL void SetGreen(uint8_t _green);
	DLL void SetBlue(uint8_t _blue);
	DLL void SetAlpha(uint8_t _alpha);

	DLL operator Color() const;
	DLL operator uint32_t() const;

private:
	uint32_t m_value;

};