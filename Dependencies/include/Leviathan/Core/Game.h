#pragma once

class Game
{
public:
	virtual ~Game() = default;

protected:
	friend class Application;

	virtual void Load(class GameManagers* _gameManagers) = 0;
	virtual void Unload(class GameManagers* _gameManagers) {}

	virtual void Tick() {}
	virtual void Render() {}

};