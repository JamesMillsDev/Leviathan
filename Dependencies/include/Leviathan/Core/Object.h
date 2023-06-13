#pragma once

#include <Leviathan/Core/Leviathan.h>

namespace Leviathan
{
	class Object
	{
	protected:
		DLL class GameStateManager* GetStateManager();
		DLL class GameObjectManager* GetObjectManager();
		DLL class GameTimerManager* GetTimerManager();
		DLL class UIManager* GetUIManager();

	};
}

