#include <Leviathan/Application.h>

#include <Leviathan/Window.h>
#include <raylib/raylib.h>

#include <Leviathan/Config.h>

Application* Application::m_instance = nullptr;

Application::Application(Game* _game) : m_game(_game), m_window(nullptr)
{
	Config::CreateInstance("config.cfg");

	m_window = new Window();
}

Application::~Application()
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

	Config::DestroyInstance();
}

void Application::process()
{
	m_window->open();

	while (!WindowShouldClose())
	{
		m_window->beginFrame();

		m_window->endFrame();
	}

	m_window->close();
}
