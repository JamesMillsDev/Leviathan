#include <Leviathan/Object.h>

#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/Utils/GameTimerManager.h>
#include <Leviathan/UI/UIManager.h>
#include <Leviathan/GameManagers.h>

namespace Leviathan
{
	TObjectPtr<GameStateManager> Object::GetStateManager()
	{
		return GameManagers::m_stateManager;
	}

	TObjectPtr<GameObjectManager> Object::GetObjectManager()
	{
		return GameManagers::m_objectManager;
	}

	TObjectPtr<GameTimerManager> Object::GetTimerManager()
	{
		return GameManagers::m_timerManager;
	}

	TObjectPtr<UIManager> Object::GetUIManager()
	{
		return GameManagers::m_uiManager;
	}
}