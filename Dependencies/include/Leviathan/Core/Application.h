#pragma once

#include <Leviathan/Core/Game.h>

#include <Leviathan/Core/Leviathan.h>
#include <Leviathan/Utils/Config.h>

#include <map>
#include <string>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;

enum class ConfigType
{
	Application,
	Window,
	Debug
};

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run(char* _argv[]);

	DLL static const char* GetApplicationDirectory();
	DLL static Config* GetConfig(ConfigType _type);
	DLL static void AddConfigReloadCallback(void(Config::*_callback)(), Config* _config);
	DLL static void GetWindowSize(int& _width, int& _height);

private:
	DLL static Application* m_instance;

	vector<pair<Config*, void(Config::*)()>> m_onConfigReload;
	struct Window* m_window;
	map<ConfigType, Config*> m_configs;
	
	Game* m_game;
	const char* m_applicationDir;

	int m_configReloadKey;

private:
	DLL Application(Game* _game);
	DLL ~Application();

	DLL void Init();
	DLL void Process();
	DLL void OnConfigReloaded(class Config* _config);

};

template<Derived<Game> GAME>
inline int Application::Run(char* _argv[])
{
	if (m_instance == nullptr)
	{
		const string argvStr(_argv[0]);
		const string base = argvStr.substr(0, argvStr.find_last_of("\\"));

		m_instance = new Application(new GAME());
		m_instance->m_applicationDir = base.c_str();
		m_instance->Process();
		return 0;
	}

	return -1;
}
