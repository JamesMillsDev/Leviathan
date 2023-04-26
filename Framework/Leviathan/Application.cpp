#include <Leviathan/Application.h>

#include <Leviathan/Window.h>
#include <raylib/raylib.h>

#include <Leviathan/Config.h>
#include <Leviathan/Resources/Resources.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

Application* Application::m_instance = nullptr;

const char* Application::GetApplicationDirectory()
{
	return m_instance->m_applicationDir;
}

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

	Resources::CreateInstance();
	GameStateManager::CreateInstance();
	GameObjectManager::CreateInstance();

	m_game->Load();

	while (!WindowShouldClose())
	{
		m_game->Tick();

		GameStateManager::Tick();
		GameObjectManager::Tick();

		m_window->BeginFrame();

		m_game->Render();

		GameStateManager::Render();
		GameObjectManager::Render();

		m_window->EndFrame();
	}

	m_game->Unload();

	GameObjectManager::DestroyInstance();
	GameStateManager::DestroyInstance();
	Resources::DestroyInstance();

	m_window->Close();
}
