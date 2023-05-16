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

class GameStateManager final : public Singleton<GameStateManager>
{
public:
	GameStateManager() = default;
	GameStateManager(GameStateManager&) = delete;
	DLL ~GameStateManager() override;

	DLL static void AddState(class IGameState* _state);
	DLL static void RemoveState(const class IGameState* _state);
	DLL static void ActivateState(const char* _id);
	DLL static void DeactivateState(const char* _id);

private:
	friend class Application;

	vector<UpdateAction> m_listUpdates;
	list<class IGameState*> m_activeStates;
	map<const char*, class IGameState*> m_states;

private:
	DLL static void Tick();
	DLL static void Render();

	DLL void AddState_Internal(class IGameState* _state);
	DLL void RemoveState_Internal(const class IGameState* _state);
	DLL void ActivateState_Internal(const char* _id);
	DLL void DeactivateState_Internal(const char* _id);

};

