#include <Leviathan/Core/Application.h>

#include <Leviathan/Core/Time.h>
#include <Leviathan/Core/Window.h>

#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/GameStates/GameStateManager.h>

#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Resources/Resources.h>

#include <Leviathan/Utils/GameTimerManager.h>
#include <Leviathan/Utils/ConfigValue.h>
#include <Leviathan/Utils/Gizmos.h>

#include <raylib/raylib.h>

Application* Application::m_instance = nullptr;

const char* Application::GetApplicationDirectory()
{
    return m_instance->m_applicationDir;
}

Config* Application::GetConfig(ConfigType _type)
{
    if(m_instance->m_configs.find(_type) == m_instance->m_configs.end())
        return nullptr;

    return m_instance->m_configs[_type];
}

void Application::AddConfigReloadCallback(void (Config::* _callback)(), Config* _config)
{
    m_instance->m_onConfigReload.push_back({ _config, _callback });
}

void Application::GetWindowSize(int& _width, int& _height)
{
    _width = m_instance->m_window->m_width;
    _height = m_instance->m_window->m_height;
}

Application::Application(Game* _game)
    : m_game(_game), m_window(nullptr), m_applicationDir(nullptr), m_configReloadKey(0),
    m_stateManager(nullptr), m_objectManager(nullptr)
{
}

Application::~Application()
{
    if(m_game != nullptr)
    {
        delete m_game;
        m_game = nullptr;
    }

    if(m_window != nullptr)
    {
        delete m_window;
        m_window = nullptr;
    }

    for(auto& config : m_configs)
    {
        if(config.second != nullptr)
        {
            delete config.second;
        }
    }

    m_configs.clear();
}

void Application::Load()
{
    m_configs[ConfigType::Application] = new Config("app.cfg");
    m_configs[ConfigType::Window] = new Config("window.cfg");
    m_configs[ConfigType::Debug] = new Config("debug.cfg");

    m_configReloadKey = m_configs[ConfigType::Debug]->GetValue("Config", "reloadConfigKey")->Get<int>();
    m_configs[ConfigType::Debug]->ListenForReload(&Application::OnConfigReloaded, this);

    m_window = new Window();
    m_window->Open();

    m_stateManager = new GameStateManager();
    m_objectManager = new GameObjectManager();

    GameTimerManager::CreateInstance();
    Resources::CreateInstance();
    PhysicsManager::CreateInstance();
    Gizmos::m_instance = new Gizmos();
    Gizmos::m_instance->Init();

    m_game->Load(m_stateManager, m_objectManager);
}

void Application::Process()
{
    Load();

    while(!WindowShouldClose())
    {
        Time::Tick();
        Gizmos::m_instance->Tick();

        if(IsKeyPressed(m_configReloadKey))
        {
            for(auto& callback : m_onConfigReload)
            {
                std::invoke(callback.second, callback.first);
            }
        }

        GameTimerManager::Tick();
        m_game->Tick();

        PhysicsManager::Tick();
        m_stateManager->Tick();
        m_objectManager->Tick();

        m_window->BeginFrame();

        m_stateManager->Render();
        m_objectManager->Render();

        m_game->Render();

        if(Gizmos::m_instance->m_shown)
        {
            m_objectManager->DrawGizmos();
        }

        m_window->EndFrame();
    }

    Unload();
}

void Application::OnConfigReloaded(Config* _config)
{
    m_configReloadKey = m_configs[ConfigType::Debug]->GetValue("Config", "reloadConfigKey")->Get<int>();
}

void Application::Unload()
{
    m_game->Unload(m_stateManager, m_objectManager);

    if (m_stateManager != nullptr)
    {
        delete m_stateManager;
        m_stateManager = nullptr;
    }

    if (m_objectManager != nullptr)
    {
        delete m_objectManager;
        m_objectManager = nullptr;
    }

    Resources::DestroyInstance();
    PhysicsManager::DestroyInstance();
    GameTimerManager::DestroyInstance();

    m_window->Close();
}
