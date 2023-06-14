#include <Leviathan/Window.h>

#include <Leviathan/Application.h>

#include <Leviathan/Utils/Config.h>
#include <Leviathan/Utils/ConfigValue.h>

#include <iostream>

#include <raylib/raylib.h>

namespace Leviathan
{
    Window::Window()
        : m_width(0), m_height(0), m_fullscreenKey(0), m_config(nullptr)
    {
    }

    void Window::Open()
    {
        m_config = Application::GetConfig(ConfigType::Window);

        m_width = m_config->GetValue(WINDOW_CATEGORY, "width")->Get<int>();
        m_height = m_config->GetValue(WINDOW_CATEGORY, "height")->Get<int>();
        m_title = m_config->GetValue(WINDOW_CATEGORY, "title")->Get<string>();
        m_clearColor = m_config->GetValue(WINDOW_CATEGORY, "clearColor")->Get<Color32>();
        m_fullscreenKey = m_config->GetValue(WINDOW_CATEGORY, "toggleFullscreenKey")->Get<int>();
        m_config->ListenForReload(&Window::OnConfigReloaded, this);

        if (m_config->GetValue(WINDOW_CATEGORY, "useFullscreen")->Get<bool>())
        {
            SetConfigFlags(FLAG_FULLSCREEN_MODE);
            m_width = m_height = 0;
        }
        else
        {
            SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        }

        InitWindow(m_width, m_height, m_title.c_str());

    }

    void Window::Close()
    {
        CloseWindow();
    }

    void Window::BeginFrame()
    {
        TryToggleFullscreen();

        BeginDrawing();
        ClearBackground(m_clearColor);

        m_width = GetScreenWidth();
        m_height = GetScreenHeight();
    }

    void Window::EndFrame()
    {
        EndDrawing();
    }

    void Window::TryToggleFullscreen()
    {
        if (IsKeyPressed(m_fullscreenKey))
        {
            if (!IsWindowFullscreen())
            {
                SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
            }

            ToggleFullscreen();

            if (!IsWindowFullscreen())
            {
                int width = m_config->GetValue(WINDOW_CATEGORY, "width")->Get<int>();
                int height = m_config->GetValue(WINDOW_CATEGORY, "height")->Get<int>();

                SetWindowSize(width, height);
            }
        }
    }

    void Window::OnConfigReloaded(Config* _config)
    {
        m_width = m_config->GetValue(WINDOW_CATEGORY, "width")->Get<int>();
        m_height = m_config->GetValue(WINDOW_CATEGORY, "height")->Get<int>();
        m_title = m_config->GetValue(WINDOW_CATEGORY, "title")->Get<string>();
        m_clearColor = m_config->GetValue(WINDOW_CATEGORY, "clearColor")->Get<Color32>();
        m_fullscreenKey = m_config->GetValue(WINDOW_CATEGORY, "toggleFullscreenKey")->Get<int>();

        SetWindowTitle(m_title.c_str());
        if (!IsWindowFullscreen())
        {
            SetWindowSize(m_width, m_height);
        }
    }
}