#include <Leviathan/Core/Object.h>

#include <Leviathan/GameStates/GameStateManager.h>
#include <Leviathan/Core/GameManagers.h>

namespace Leviathan
{
	GameStateManager* Object::GetStateManager()
	{
		return GameManagers::m_stateManager;
	}

	GameObjectManager* Object::GetObjectManager()
	{
		return nullptr;
	}

	GameTimerManager* Object::GetTimerManager()
	{
		return nullptr;
	}

	UIManager* Object::GetUIManager()
	{
		return nullptr;
	}
}