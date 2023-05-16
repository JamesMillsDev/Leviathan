#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Game.h>
#include <Leviathan/Config.h>

#include <map>
#include <vector>
#include <string>
#include <functional>

using std::map;
using std::vector;
using std::string;
using std::function;
using std::pair;

enum class ConfigType
{
	APPLICATION,
	WINDOW,
	DEBUG
};

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run(char* argv[]);

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
inline int Application::Run(char* argv[])
{
	if (m_instance == nullptr)
	{
		string argv_str(argv[0]);
		string base = argv_str.substr(0, argv_str.find_last_of("\\"));

		m_instance = new Application(new GAME());
		m_instance->m_applicationDir = base.c_str();
		m_instance->Process();
		return 0;
	}

	return -1;
}
