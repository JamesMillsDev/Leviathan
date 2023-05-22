#pragma once

class Game
{
public:
	virtual ~Game() = default;

protected:
	friend class Application;

	virtual void Load(class GameStateManager* _stateManager, class GameObjectManager* _objectManager) = 0;
	virtual void Unload(class GameStateManager* _stateManager, class GameObjectManager* _objectManager) {}

	virtual void Tick() {}
	virtual void Render() {}

};