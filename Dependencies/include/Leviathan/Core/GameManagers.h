#pragma once

#include <Leviathan/Core/Leviathan.h>

class GameManagers
{
private:
	friend class Application;
	friend class GameStateManager* GetStateManager();
	friend class GameObjectManager* GetObjectManager();
	friend class GameTimerManager* GetTimerManager();

	DLL static class GameStateManager* m_stateManager;
	DLL static class GameObjectManager* m_objectManager;
	DLL static class GameTimerManager* m_timerManager;

private:
	DLL GameManagers();
	DLL ~GameManagers();
	GameManagers(GameManagers&) = delete;
	GameManagers(GameManagers&&) = delete;

	DLL void Tick();
	DLL void Render();
	DLL void DrawGizmos();

};

extern class GameStateManager* GetStateManager();
extern class GameObjectManager* GetObjectManager();
extern class GameTimerManager* GetTimerManager();