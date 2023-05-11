#include <Leviathan/Application.h>

#include <Leviathan/Window.h>
#include <raylib.h>

#include <Leviathan/Config.h>
#include <Leviathan/Gizmos.h>
#include <Leviathan/Resources/Resources.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/Physics/PhysicsManager.h>

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

void Application::AddConfigReloadCallback(ReloadCallback _callback)
{
	m_instance->m_onConfigReload.push_back(_callback);
}

void Application::GetWindowSize(int& _width, int& _height)
{
	_width = m_instance->m_window->m_width;
	_height = m_instance->m_window->m_height;
}

Application::Application(Game* _game) 
	: m_game(_game), m_window(nullptr), m_applicationDir(nullptr), m_configReloadKey(0)
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

	m_configReloadKey = *m_configs[ConfigType::DEBUG]->GetValue<int>("Config", "reloadConfigKey");
	m_configs[ConfigType::DEBUG]->ListenForReload(std::bind(&Application::OnConfigReloaded, this, m_configs[ConfigType::DEBUG]));

	m_window = new Window();
}

void Application::Process()
{
	Init();

	m_window->Open();

	Resources::CreateInstance();
	PhysicsManager::CreateInstance();
	GameStateManager::CreateInstance();
	GameObjectManager::CreateInstance();
	Gizmos::Init();

	m_game->Load();

	while (!WindowShouldClose())
	{
		Gizmos::Tick();

		if (IsKeyPressed(m_configReloadKey))
		{
			for (auto& callback : m_onConfigReload)
			{
				callback();
			}
		}

		m_game->Tick();

		PhysicsManager::Tick();
		GameStateManager::Tick();
		GameObjectManager::Tick();

		m_window->BeginFrame();

		GameStateManager::Render();
		GameObjectManager::Render();

		m_game->Render();

		if (Gizmos::m_shown)
		{
			GameObjectManager::DrawGizmos();
		}

		m_window->EndFrame();
	}

	m_game->Unload();

	GameObjectManager::DestroyInstance();
	GameStateManager::DestroyInstance();
	Resources::DestroyInstance();

	m_window->Close();
}

void Application::OnConfigReloaded(Config* _config)
{
	m_configReloadKey = *m_configs[ConfigType::DEBUG]->GetValue<int>("Config", "reloadConfigKey");
}
