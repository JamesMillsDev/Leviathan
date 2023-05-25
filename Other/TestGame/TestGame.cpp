#include "TestGame.h"

#include <Leviathan/Core/GameManagers.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>

#include "PlayState.h"

void TestGame::Load(GameManagers* _gameManagers)
{
	GetStateManager()->AddState(new PlayState(_gameManagers));

	GetStateManager()->ActivateState("PLAY");
}