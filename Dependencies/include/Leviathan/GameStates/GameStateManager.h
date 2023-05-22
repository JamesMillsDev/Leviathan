#pragma once

#include <Leviathan/Core/Leviathan.h>
#include <Leviathan/Utils/Singleton.h>

#include <functional>
#include <list>
#include <map>
#include <vector>

using std::function;
using std::vector;
using std::list;
using std::map;

typedef function<void()> UpdateAction;

class GameStateManager
{
public:
	GameStateManager() = default;
	GameStateManager(GameStateManager&) = delete;
	DLL ~GameStateManager();

	DLL void AddState(class IGameState* _state);
	DLL void RemoveState(const class IGameState* _state);
	DLL void ActivateState(const char* _id);
	DLL void DeactivateState(const char* _id);

private:
	friend class Application;

	vector<UpdateAction> m_listUpdates;
	list<class IGameState*> m_activeStates;
	map<const char*, class IGameState*> m_states;

private:
	DLL void Tick();
	DLL void Render();

};

