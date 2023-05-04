#include <Leviathan/window.h>

#include <raylib.h>

#include <Leviathan/Application.h>
#include <Leviathan/Config.h>

#include <iostream>

Window::Window() 
	: m_config(nullptr), m_height(0), m_width(0), 
	m_title(nullptr), m_fullscreenKey(0)
{
	
}

void Window::Open()
{
	m_config = Application::GetConfig(ConfigType::WINDOW);

	m_width = *m_config->GetValue<int>(WINDOW_CATEGORY, "width");
	m_height = *m_config->GetValue<int>(WINDOW_CATEGORY, "height");
	m_title = m_config->GetValue<string>(WINDOW_CATEGORY, "title")->c_str();
	m_clearColor = *m_config->GetValue<Color32>(WINDOW_CATEGORY, "clearColor");
	m_fullscreenKey = *m_config->GetValue<int>(WINDOW_CATEGORY, "toggleFullscreenKey");
	m_config->ListenForReload(std::bind(&Window::OnConfigReloaded, this, m_config));

	InitWindow(m_width, m_height, m_title);
}

void Window::Close()
{
	CloseWindow();
}

void Window::BeginFrame()
{
	TryToggleFullscreen();

	BeginDrawing();
	ClearBackground(m_clearColor);

	m_width = GetScreenWidth();
	m_height = GetScreenHeight();
}

void Window::EndFrame()
{
	EndDrawing();
}

void Window::TryToggleFullscreen()
{
	if (IsKeyPressed(m_fullscreenKey))
	{
		if (!IsWindowFullscreen())
		{
			SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
		}

		ToggleFullscreen();

		if (!IsWindowFullscreen())
		{
			int width = *m_config->GetValue<int>(WINDOW_CATEGORY, "width");
			int height = *m_config->GetValue<int>(WINDOW_CATEGORY, "height");

			SetWindowSize(width, height);
		}
	}
}

void Window::OnConfigReloaded(Config* _config)
{
	m_width = *_config->GetValue<int>(WINDOW_CATEGORY, "width");
	m_height = *_config->GetValue<int>(WINDOW_CATEGORY, "height");
	m_title = _config->GetValue<string>(WINDOW_CATEGORY, "title")->c_str();
	m_clearColor = *_config->GetValue<Color32>(WINDOW_CATEGORY, "clearColor");
	m_fullscreenKey = *_config->GetValue<int>(WINDOW_CATEGORY, "toggleFullscreenKey");

	SetWindowTitle(m_title);
	if (!IsWindowFullscreen())
	{
		SetWindowSize(m_width, m_height);
	}
}
