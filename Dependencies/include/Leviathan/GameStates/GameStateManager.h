#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Singleton.h>

#include <functional>
#include <vector>
#include <map>

using std::function;
using std::vector;
using std::map;

typedef function<void()> UpdateAction;

class GameStateManager : public Singleton<GameStateManager>
{
public:
	GameStateManager() = default;
	GameStateManager(GameStateManager&) = delete;
	DLL ~GameStateManager();

	DLL static void AddState(class IGameState* _state);
	DLL static void RemoveState(class IGameState* _state);
	DLL static void ActivateState(char* _id);
	DLL static void DeactivateState(char* _id);

private:
	friend class Application;

	vector<UpdateAction> m_listUpdates;
	vector<class IGameState*> m_activeStates;
	map<char*, class IGameState*> m_states;

private:
	DLL static void Tick();
	DLL static void Render();

};

