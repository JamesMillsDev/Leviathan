#include <Leviathan/window.h>

#include <raylib.h>

#include <Leviathan/Application.h>
#include <Leviathan/Config.h>

Window::Window() : m_config(nullptr), m_height(0), m_width(0), m_title(nullptr)
{
	
}

void Window::Open()
{
	m_config = Application::GetConfig(ConfigType::WINDOW);

	m_width = *m_config->GetValue<int>(WINDOW_CATEGORY, "width");
	m_height = *m_config->GetValue<int>(WINDOW_CATEGORY, "height");
	m_title = m_config->GetValue<string>(WINDOW_CATEGORY, "title")->c_str();
	m_clearColor = *m_config->GetValue<Color32>(WINDOW_CATEGORY, "clearColor");

	InitWindow(m_width, m_height, m_title);
}

void Window::Close()
{
	CloseWindow();
}

void Window::BeginFrame()
{
	BeginDrawing();
	ClearBackground(m_clearColor);
}

void Window::EndFrame()
{
	EndDrawing();
}
