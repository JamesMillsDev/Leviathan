#pragma once

struct window
{
private:
	friend class application;

	int m_width;
	int m_height;
	const char* m_title;

	window(int _width, int _height, const char* _title);
	window(window&) = delete;
	~window() = default;

	void open();
	void close();

	void beginFrame();
	void endFrame();

};