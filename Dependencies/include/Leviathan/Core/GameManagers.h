#pragma once

#include <Leviathan/Core/Leviathan.h>

class GameManagers
{
public:
	class GameStateManager* stateManager;
	class GameObjectManager* objectManager;
	class GameTimerManager* timerManager;

private:
	friend class Application;

private:
	DLL GameManagers();
	DLL ~GameManagers();
	GameManagers(GameManagers&) = delete;
	GameManagers(GameManagers&&) = delete;

	DLL void Tick();
	DLL void Render();
	DLL void DrawGizmos();

};