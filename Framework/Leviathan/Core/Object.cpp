#include <Leviathan/Core/Object.h>

#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/Utils/GameTimerManager.h>
#include <Leviathan/UI/UIManager.h>
#include <Leviathan/Core/GameManagers.h>

namespace Leviathan
{
	GameStateManager* Object::GetStateManager()
	{
		return GameManagers::m_stateManager;
	}

	GameObjectManager* Object::GetObjectManager()
	{
		return GameManagers::m_objectManager;
	}

	GameTimerManager* Object::GetTimerManager()
	{
		return GameManagers::m_timerManager;
	}

	UIManager* Object::GetUIManager()
	{
		return GameManagers::m_uiManager;
	}
}