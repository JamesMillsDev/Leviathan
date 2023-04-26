#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Game.h>

#include <string>

using std::string;

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run(char* argv[]);

	static const char* GetApplicationDirectory();

private:
	DLL static Application* m_instance;

	struct Window* m_window;
	
	Game* m_game;
	const char* m_applicationDir;

	DLL Application(Game* _game);
	DLL ~Application();

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
