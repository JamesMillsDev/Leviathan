#pragma once

#include <Leviathan/game.h>

#include <concepts>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class Application
{
public:
	template<Derived<Game> GAME>
	static int run();

private:
	static Application* m_instance;

	struct Window* m_window;
	
	Game* m_game;

	Application(Game* _game);
	~Application();

	void process();

};

template<Derived<Game> GAME>
inline int Application::run()
{
	if (m_instance == nullptr)
	{
		m_instance = new Application(new GAME());
		m_instance->process();
		return 0;
	}

	return -1;
}
