#include "TestGame.h"

#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include "PlayState.h"

void TestGame::Load(GameStateManager* _stateManager, GameObjectManager* _objectManager)
{
	_stateManager->AddState(new PlayState(_stateManager, _objectManager));

	_stateManager->ActivateState("PLAY");
}