#include <Leviathan/window.h>

#include <raylib/raylib.h>

#include <Leviathan/config.h>

window::window()
{
	m_width = config::getIntValue(WINDOW_CATEGORY, "width");
	m_height = config::getIntValue(WINDOW_CATEGORY, "height");
	m_title = config::getTextValue(PROGRAM_CATEGORY, "title");
	m_clearColor = config::getColorValue(PROGRAM_CATEGORY, "clearColor");
}

void window::open()
{
	InitWindow(m_width, m_height, m_title);
}

void window::close()
{
	CloseWindow();
}

void window::beginFrame()
{
	BeginDrawing();
	ClearBackground(m_clearColor);
}

void window::endFrame()
{
	EndDrawing();
}
