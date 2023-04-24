#include <Leviathan/window.h>

#include <raylib/raylib.h>

#include <Leviathan/config.h>

Window::Window()
{
	m_width = Config::GetIntValue(WINDOW_CATEGORY, "width");
	m_height = Config::GetIntValue(WINDOW_CATEGORY, "height");
	m_title = Config::GetTextValue(PROGRAM_CATEGORY, "title");
	m_clearColor = Config::GetColorValue(PROGRAM_CATEGORY, "clearColor");
}

void Window::open()
{
	InitWindow(m_width, m_height, m_title);
}

void Window::close()
{
	CloseWindow();
}

void Window::beginFrame()
{
	BeginDrawing();
	ClearBackground(m_clearColor);
}

void Window::endFrame()
{
	EndDrawing();
}
