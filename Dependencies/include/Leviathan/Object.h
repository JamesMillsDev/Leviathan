#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/TObjectPtr.h>

namespace Leviathan
{
	class Object
	{
	protected:
		DLL TObjectPtr<class GameStateManager> GetStateManager();
		DLL TObjectPtr<class GameObjectManager> GetObjectManager();
		DLL TObjectPtr<class GameTimerManager> GetTimerManager();
		DLL TObjectPtr<class UIManager> GetUIManager();

	};
}

