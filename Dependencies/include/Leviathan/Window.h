#pragma once

#include <Leviathan/Leviathan.h>

#include <Leviathan/Color32.h>

struct Window
{
private:
	friend class Application;

	int m_width;
	int m_height;
	int m_fullscreenKey;
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
	DLL void TryToggleFullscreen();
	DLL void OnConfigReloaded(class Config* _config);

};