#pragma once

#include <Leviathan/Leviathan.h>

#include <Leviathan/Math/Color32.h>

struct Window
{
private:
	friend class Application;

	int m_width;
	int m_height;
	const char* m_title;
	Color32 m_clearColor;
	class Config* m_config;

private:
	DLL Window();
	Window(Window&) = delete;
	~Window() = default;

	DLL void Open();
	DLL void Close();

	DLL void BeginFrame();
	DLL void EndFrame();

};