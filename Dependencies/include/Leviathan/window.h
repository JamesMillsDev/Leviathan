#pragma once

#include <Leviathan/Math/color.h>

struct window
{
private:
	friend class application;

	int m_width;
	int m_height;
	const char* m_title;
	color m_clearColor;

	window();
	window(window&) = delete;
	~window() = default;

	void open();
	void close();

	void beginFrame();
	void endFrame();

};