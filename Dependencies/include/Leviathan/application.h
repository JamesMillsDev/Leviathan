#pragma once

#include <Leviathan/game.h>

#include <concepts>

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class application
{
public:
	template<Derived<game> GAME>
	static int run();

private:
	static application* m_instance;

	struct window* m_window;
	
	game* m_game;

	application(game* _game);
	~application();

	void process();

};

template<Derived<game> GAME>
inline int application::run()
{
	if (m_instance == nullptr)
	{
		m_instance = new application(new GAME());
		m_instance->process();
		return 0;
	}

	return -1;
}
