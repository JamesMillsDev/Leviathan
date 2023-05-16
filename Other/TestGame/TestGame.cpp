#include "TestGame.h"

#include <Leviathan/GameStates/GameStateManager.h>

#include "PlayState.h"

void TestGame::Load()
{
	GameStateManager::AddState(new PlayState());

	GameStateManager::ActivateState("PLAY");
}