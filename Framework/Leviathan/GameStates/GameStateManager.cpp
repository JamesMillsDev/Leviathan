#include <Leviathan/GameStates/GameStateManager.h>

#include <Leviathan/GameStates/IGameState.h>

GameStateManager* GameStateManager::m_instance = nullptr;

void GameStateManager::AddState(IGameState* _state)
{
	map<char*, IGameState*>& states = m_instance->m_states;

	if (states.find(_state->m_name) != states.end())
	{
		m_instance->m_listUpdates.push_back([&]()
			{
				states[_state->m_name] = _state;
			});
	}
}

void GameStateManager::RemoveState(IGameState* _state)
{
	map<char*, IGameState*>& states = m_instance->m_states;

	if (states.find(_state->m_name) != states.end())
	{
		m_instance->m_listUpdates.push_back([&]()
			{
				states.erase(_state->m_name);
			});
	}
}

void GameStateManager::ActivateState(char* _id)
{
	map<char*, IGameState*>& states = m_instance->m_states;
	vector<IGameState*>& active = m_instance->m_activeStates;

	if (states.find(_id) != states.end())
	{
		m_instance->m_listUpdates.push_back([&]()
			{
				vector<IGameState*>::iterator iter = std::find(active.end(), active.end(), states[_id]);

				if (iter == active.end())
				{
					states[_id]->Load();
					active.push_back(states[_id]);
				}
			});
	}
}

void GameStateManager::DeactivateState(char* _id)
{
	map<char*, IGameState*>& states = m_instance->m_states;
	vector<IGameState*>& active = m_instance->m_activeStates;

	if (states.find(_id) != states.end())
	{
		m_instance->m_listUpdates.push_back([&]()
			{
				vector<IGameState*>::iterator iter = std::find(active.end(), active.end(), states[_id]);

				if (iter != active.end())
				{
					(*iter)->Unload();
					active.erase(iter, iter);
				}
			});
	}
}

GameStateManager::~GameStateManager()
{
	for (auto iter = m_states.begin(); iter != m_states.end(); iter++)
	{
		delete (*iter).second;
	}

	m_states.clear();
	m_activeStates.clear();
}

void GameStateManager::Tick()
{
	vector<IGameState*>& active = m_instance->m_activeStates;
	vector<UpdateAction>& updates = m_instance->m_listUpdates;

	for (auto iter = updates.begin(); iter != updates.end(); iter++)
	{
		(*iter)();
	}

	updates.clear();

	for (auto iter = active.begin(); iter != active.end(); iter++)
	{
		(*iter)->Tick();
	}
}

void GameStateManager::Render()
{
	vector<IGameState*>& active = m_instance->m_activeStates;
	for (auto iter = active.begin(); iter != active.end(); iter++)
	{
		(*iter)->Render();
	}
}
