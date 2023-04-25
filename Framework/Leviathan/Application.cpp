#include <Leviathan/Application.h>

#include <Leviathan/Window.h>
#include <raylib/raylib.h>

#include <Leviathan/Config.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

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

void Application::Process()
{
	m_window->Open();

	GameStateManager::CreateInstance();
	GameObjectManager::CreateInstance();

	while (!WindowShouldClose())
	{
		GameStateManager::Tick();
		GameObjectManager::Tick();

		m_window->BeginFrame();

		GameStateManager::Render();
		GameObjectManager::Render();

		m_window->EndFrame();
	}

	GameObjectManager::DestroyInstance();
	GameStateManager::DestroyInstance();

	m_window->Close();
}
