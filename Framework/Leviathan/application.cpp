#include <Leviathan/application.h>

#include <Leviathan/window.h>
#include <raylib/raylib.h>

#include <Leviathan/config.h>

application* application::m_instance = nullptr;

application::application(game* _game) : m_game(_game), m_window(nullptr)
{
	config::createInstance("config.cfg");

	m_window = new window();
}

application::~application()
{
	if (m_game != nullptr)
	{
		delete m_game;
		m_game = nullptr;
	}

	if (m_window != nullptr)
	{
		delete m_window;
		m_window = nullptr;
	}

	config::destroyInstance();
}

void application::process()
{
	m_window->open();

	while (!WindowShouldClose())
	{
		m_window->beginFrame();

		m_window->endFrame();
	}

	m_window->close();
}
