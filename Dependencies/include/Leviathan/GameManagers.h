#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/TObjectPtr.h>

namespace Leviathan
{
	class GameManagers
	{
	private:
		friend class Application;
		friend class Object;

		DLL static TObjectPtr<class GameStateManager> m_stateManager;
		DLL static TObjectPtr<class GameObjectManager> m_objectManager;
		DLL static TObjectPtr<class GameTimerManager> m_timerManager;
		DLL static TObjectPtr<class UIManager> m_uiManager;

	private:
		DLL GameManagers();
		DLL ~GameManagers();
		GameManagers(GameManagers&) = delete;
		GameManagers(GameManagers&&) = delete;

		DLL void Tick();
		DLL void Render();
		DLL void DrawGizmos();

	};
}