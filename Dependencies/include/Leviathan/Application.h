#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Game.h>

#include <concepts>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run();

private:
	DLL static Application* m_instance;

	struct Window* m_window;
	
	Game* m_game;

	DLL Application(Game* _game);
	DLL ~Application();

	DLL void Process();

};

template<Derived<Game> GAME>
inline int Application::Run()
{
	if (m_instance == nullptr)
	{
		m_instance = new Application(new GAME());
		m_instance->Process();
		return 0;
	}

	return -1;
}
