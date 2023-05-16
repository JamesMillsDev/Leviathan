#include <Leviathan/GameStates/GameStateManager.h>

#include <Leviathan/GameStates/IGameState.h>

void GameStateManager::AddState(IGameState* _state)
{
    m_instance->AddState_Internal(_state);
}

void GameStateManager::RemoveState(const IGameState* _state)
{
    m_instance->RemoveState_Internal(_state);
}

void GameStateManager::ActivateState(const char* _id)
{
    m_instance->ActivateState_Internal(_id);
}

void GameStateManager::DeactivateState(const char* _id)
{
    m_instance->DeactivateState_Internal(_id);
}

GameStateManager::~GameStateManager()
{
    for(auto iter = m_states.begin(); iter != m_states.end(); ++iter)
        delete (*iter).second;

    m_states.clear();
    m_activeStates.clear();
}

void GameStateManager::Tick()
{
    list<IGameState*>& active = m_instance->m_activeStates;
    vector<UpdateAction>& updates = m_instance->m_listUpdates;

    for(auto iter = updates.begin(); iter != updates.end(); ++iter)
        (*iter)();

    updates.clear();

    for(auto iter = active.begin(); iter != active.end(); ++iter)
        (*iter)->Tick();
}

void GameStateManager::Render()
{
    list<IGameState*>& active = m_instance->m_activeStates;
    for(auto iter = active.begin(); iter != active.end(); ++iter)
        (*iter)->Render();
}

void GameStateManager::AddState_Internal(IGameState* _state)
{
    m_listUpdates.emplace_back([=, this]()
    {
        if(!m_states.contains(_state->m_name))
            m_states[_state->m_name] = _state;
    });
}

DLL void GameStateManager::RemoveState_Internal(const IGameState* _state)
{
    m_listUpdates.emplace_back([=, this]()
    {
        if(m_states.contains(_state->m_name))
            m_states.erase(_state->m_name);
    });
}

void GameStateManager::ActivateState_Internal(const char* _id)
{
    m_listUpdates.emplace_back([=, this]()
    {
        if(m_states.contains(_id))
        {
            const list<IGameState*>::iterator iter = std::find(m_activeStates.begin(), m_activeStates.end(), m_states[_id]);

            if(iter == m_activeStates.end())
            {
                m_states[_id]->Load();
                m_activeStates.push_back(m_states[_id]);
            }
        }
    });
}

void GameStateManager::DeactivateState_Internal(const char* _id)
{
    m_listUpdates.emplace_back([=, this]()
    {
        if(m_states.contains(_id))
        {
            const list<IGameState*>::iterator iter = std::find(m_activeStates.begin(), m_activeStates.end(), m_states[_id]);

            if(iter != m_activeStates.end())
            {
                (*iter)->Unload();
                m_activeStates.erase(iter);
            }
        }
    });
}
