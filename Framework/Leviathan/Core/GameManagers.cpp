#include <Leviathan/Core/GameManagers.h>

#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/Utils/GameTimerManager.h>

GameStateManager* GameManagers::m_stateManager = nullptr;
GameObjectManager* GameManagers::m_objectManager = nullptr;
GameTimerManager* GameManagers::m_timerManager = nullptr;

GameManagers::GameManagers()
{
	m_stateManager = new GameStateManager();
	m_objectManager = new GameObjectManager();
	m_timerManager = new GameTimerManager();
}

GameManagers::~GameManagers()
{
	if (m_stateManager != nullptr)
	{
		delete m_stateManager;
		m_stateManager = nullptr;
	}

	if (m_objectManager != nullptr)
	{
		delete m_objectManager;
		m_objectManager = nullptr;
	}

	if (m_timerManager != nullptr)
	{
		delete m_timerManager;
		m_timerManager = nullptr;
	}
}

void GameManagers::Tick()
{
	if (m_timerManager != nullptr)
		m_timerManager->Tick();

	if (m_stateManager != nullptr)
		m_stateManager->Tick();

	if (m_objectManager != nullptr)
		m_objectManager->Tick();
}

void GameManagers::Render()
{
	if (m_stateManager != nullptr)
		m_stateManager->Render();

	if (m_objectManager != nullptr)
		m_objectManager->Render();
}

void GameManagers::DrawGizmos()
{
	if (m_objectManager != nullptr)
		m_objectManager->DrawGizmos();
}