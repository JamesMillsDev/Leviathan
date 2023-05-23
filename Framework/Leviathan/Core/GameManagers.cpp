#include <Leviathan/Core/GameManagers.h>

#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/Utils/GameTimerManager.h>

GameManagers::GameManagers() 
	: stateManager(new GameStateManager()), objectManager(new GameObjectManager()), 
	timerManager(new GameTimerManager())
{
	
}

GameManagers::~GameManagers()
{
	if (stateManager != nullptr)
	{
		delete stateManager;
		stateManager = nullptr;
	}

	if (objectManager != nullptr)
	{
		delete objectManager;
		objectManager = nullptr;
	}

	if (timerManager != nullptr)
	{
		delete timerManager;
		timerManager = nullptr;
	}
}

void GameManagers::Tick()
{
	if (timerManager != nullptr)
		timerManager->Tick();

	if (stateManager != nullptr)
		stateManager->Tick();

	if (objectManager != nullptr)
		objectManager->Tick();
}

void GameManagers::Render()
{
	if (stateManager != nullptr)
		stateManager->Render();

	if (objectManager != nullptr)
		objectManager->Render();
}

void GameManagers::DrawGizmos()
{
	if (objectManager != nullptr)
		objectManager->DrawGizmos();
}
