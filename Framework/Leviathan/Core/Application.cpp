#include <Leviathan/Application.h>

#include <Leviathan/Time.h>
#include <Leviathan/Window.h>
#include <Leviathan/GameManagers.h>

#include <Leviathan/Physics/PhysicsManager.h>

#include <Leviathan/Resources/Resources.h>

#include <Leviathan/Utils/ConfigValue.h>
#include <Leviathan/Utils/Gizmos.h>

#include <raylib/raylib.h>

namespace Leviathan
{
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

    void Application::AddConfigReloadCallback(void (Config::* _callback)(), Config* _config)
    {
        m_instance->m_onConfigReload.push_back({ _config, _callback });
    }

    void Application::GetWindowSize(int& _width, int& _height)
    {
        _width = m_instance->m_window->m_width;
        _height = m_instance->m_window->m_height;
    }

    void Application::Quit()
    {
        m_instance->m_running = false;
    }

    Application::Application(Game* _game)
        : m_game(_game), m_window(nullptr), m_applicationDir(nullptr),
        m_configReloadKey(0), m_managers(nullptr), m_running(true)
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

        if (m_managers != nullptr)
        {
            delete m_managers;
            m_managers = nullptr;
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

    void Application::Load()
    {
        m_configs[ConfigType::Application] = new Config("app.cfg");
        m_configs[ConfigType::Window] = new Config("window.cfg");
        m_configs[ConfigType::Debug] = new Config("debug.cfg");

        m_configReloadKey = m_configs[ConfigType::Debug]->GetValue("Config", "reloadConfigKey")->Get<int>();
        m_configs[ConfigType::Debug]->ListenForReload(&Application::OnConfigReloaded, this);

        m_window = new Window();
        m_window->Open();

        m_managers = new GameManagers();

        Resources::CreateInstance();
        PhysicsManager::CreateInstance();
        Gizmos::m_instance = new Gizmos();
        Gizmos::m_instance->Init();

        m_game->Load();
    }

    void Application::Process()
    {
        Load();

        while (m_running)
        {
            Time::Tick();
            Gizmos::m_instance->Tick();

            if (IsKeyPressed(m_configReloadKey))
            {
                for (auto& callback : m_onConfigReload)
                    (callback.first->*callback.second)();
            }

            m_game->Tick();
            PhysicsManager::Tick();
            m_managers->Tick();

            m_window->BeginFrame();

            m_game->Render();
            m_managers->Render();

            if (Gizmos::m_instance->m_shown)
                m_managers->DrawGizmos();

            m_window->EndFrame();

            if (WindowShouldClose())
                m_running = false;
        }

        Unload();
    }

    void Application::OnConfigReloaded(Config* _config)
    {
        m_configReloadKey = m_configs[ConfigType::Debug]->GetValue("Config", "reloadConfigKey")->Get<int>();
    }

    void Application::Unload()
    {
        m_game->Unload();

        if (m_managers != nullptr)
        {
            delete m_managers;
            m_managers = nullptr;
        }

        Resources::DestroyInstance();
        PhysicsManager::DestroyInstance();

        m_window->Close();
    }
}
