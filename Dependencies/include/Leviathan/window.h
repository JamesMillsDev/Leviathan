#pragma once

#include <Leviathan/Math/Color32.h>

struct Window
{
private:
	friend class Application;

	int m_width;
	int m_height;
	const char* m_title;
	Color32 m_clearColor;

	Window();
	Window(Window&) = delete;
	~Window() = default;

	void Open();
	void Close();

	void BeginFrame();
	void EndFrame();

};