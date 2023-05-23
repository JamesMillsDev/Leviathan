#include "TestGame.h"

#include <Leviathan/Core/GameManagers.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include "PlayState.h"

void TestGame::Load(GameManagers* _gameManagers)
{
	_gameManagers->stateManager->AddState(new PlayState(_gameManagers));

	_gameManagers->stateManager->ActivateState("PLAY");
}