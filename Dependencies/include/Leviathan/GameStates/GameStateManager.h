#pragma once

#include <functional>
#include <vector>
#include <map>

using std::function;
using std::vector;
using std::map;

typedef function<void()> UpdateAction;

class GameStateManager
{
public:
	static void AddState(class IGameState* _state);
	static void RemoveState(class IGameState* _state);
	static void ActivateState(char* _id);
	static void DeactivateState(char* _id);

private:
	friend class Application;

	static GameStateManager* m_instance;

	vector<UpdateAction> m_listUpdates;
	vector<class IGameState*> m_activeStates;
	map<char*, class IGameState*> m_states;

	GameStateManager() = default;
	GameStateManager(GameStateManager&) = delete;
	~GameStateManager();

	static void CreateInstance();
	static void DestroyInstance();

	static void Tick();
	static void Render();

};

