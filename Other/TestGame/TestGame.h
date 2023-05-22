#pragma once

#include <Leviathan/Core/Game.h>

class TestGame : public Game
{
protected:
	virtual void Load(class GameStateManager* _stateManager, class GameObjectManager* _objectManager) override;

};