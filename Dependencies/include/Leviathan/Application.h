#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Game.h>
#include <Leviathan/Config.h>

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;
using std::pair;

enum class ConfigType
{
	APPLICATION,
	WINDOW,
	DEBUG
};

typedef void(Config::*ReloadCallback)();

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run(char* argv[]);

	DLL static const char* GetApplicationDirectory();
	DLL static Config* GetConfig(ConfigType _type);
	DLL static void AddConfigReloadCallback(ReloadCallback _callback, class Config* _config);

private:
	DLL static Application* m_instance;

	vector<pair<ReloadCallback, class Config*>> m_onConfigReload;
	struct Window* m_window;
	map<ConfigType, Config*> m_configs;
	
	Game* m_game;
	const char* m_applicationDir;

	int m_configReloadKey;

	DLL Application(Game* _game);
	DLL ~Application();

	DLL void Init();
	DLL void Process();

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
