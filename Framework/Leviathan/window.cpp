#include <Leviathan/window.h>

#include <raylib/raylib.h>

window::window(int _width, int _height, const char* _title) 
	: m_width(_width), m_height(_height), m_title(_title)
{
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
	ClearBackground(RAYWHITE);
}

void window::endFrame()
{
	EndDrawing();
}
