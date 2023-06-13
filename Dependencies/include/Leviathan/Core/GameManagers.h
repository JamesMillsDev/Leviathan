#pragma once

#include <Leviathan/Core/Leviathan.h>

class GameManagers
{
private:
	friend class Application;
	friend class IManagerReciever;

	DLL static class GameStateManager* m_stateManager;
	DLL static class GameObjectManager* m_objectManager;
	DLL static class GameTimerManager* m_timerManager;
	DLL static class UIManager* m_uiManager;

private:
	DLL GameManagers();
	DLL ~GameManagers();
	GameManagers(GameManagers&) = delete;
	GameManagers(GameManagers&&) = delete;

	DLL void Tick();
	DLL void Render();
	DLL void DrawGizmos();

};