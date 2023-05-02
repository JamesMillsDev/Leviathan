#include <Leviathan/Application.h>

#include <Leviathan/Window.h>
#include <raylib.h>

#include <Leviathan/Config.h>
#include <Leviathan/Resources/Resources.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

using std::invoke;

Application* Application::m_instance = nullptr;

const char* Application::GetApplicationDirectory()
{
	return m_instance->m_applicationDir;
}

Config* Application::GetConfig(ConfigType _type)
{
	if (m_instance->m_configs.find(_type) == m_instance->m_configs.end())
		return nullptr;

	return m_instance->m_configs[_type];
}

void Application::AddConfigReloadCallback(ReloadCallback _callback, Config* _config)
{
	m_instance->m_onConfigReload.push_back({ _callback, _config });
}

Application::Application(Game* _game) : m_game(_game), m_window(nullptr), m_applicationDir(nullptr)
{
	
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

	for (auto& config : m_configs)
	{
		if (config.second != nullptr)
		{
			delete config.second;
		}
	}

	m_configs.clear();
}

void Application::Init()
{
	m_configs[ConfigType::APPLICATION] = new Config("app.cfg");
	m_configs[ConfigType::WINDOW] = new Config("window.cfg");
	m_configs[ConfigType::DEBUG] = new Config("debug.cfg");

	m_configReloadKey = *m_configs[ConfigType::DEBUG]->GetValue<int>("Debug", "reloadConfigKey");

	m_window = new Window();
}

void Application::Process()
{
	Init();

	m_window->Open();

	Resources::CreateInstance();
	GameStateManager::CreateInstance();
	GameObjectManager::CreateInstance();

	m_game->Load();

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(m_configReloadKey))
		{
			for (auto& callback : m_onConfigReload)
			{
				invoke(callback.first, callback.second);
			}
		}

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
