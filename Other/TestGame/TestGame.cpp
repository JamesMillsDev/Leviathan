#include "TestGame.h"

#include <Leviathan/GameManagers.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include "PlayState.h"

void TestGame::Load()
{
	GetStateManager()->AddState(new PlayState());

	GetStateManager()->ActivateState("PLAY");
}