#pragma once

#include <Leviathan/Core/Color32.h>

#include <Leviathan/Core/Leviathan.h>

#include <string>

using std::string;

namespace Leviathan
{
	struct Window
	{
	private:
		friend class Application;

		int m_width;
		int m_height;
		int m_fullscreenKey;
		string m_title;
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
}