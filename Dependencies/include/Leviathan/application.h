#pragma once

#include <Leviathan/game.h>

#include <concepts>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run();

private:
	static Application* m_instance;

	struct Window* m_window;
	
	Game* m_game;

	Application(Game* _game);
	~Application();

	void Process();

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
