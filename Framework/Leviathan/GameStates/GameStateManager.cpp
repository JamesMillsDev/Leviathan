#include <Leviathan/GameStates/GameStateManager.h>

#include <Leviathan/GameStates/IGameState.h>

namespace Leviathan
{
    void GameStateManager::AddState(IGameState* _state)
    {
        m_listUpdates.emplace_back([=, this]()
            {
                if (!m_states.contains(_state->m_name))
                    m_states[_state->m_name] = _state;
            });
    }

    void GameStateManager::RemoveState(const IGameState* _state)
    {
        m_listUpdates.emplace_back([=, this]()
            {
                if (m_states.contains(_state->m_name))
                    m_states.erase(_state->m_name);
            });
    }

    void GameStateManager::ActivateState(const char* _id)
    {
        m_listUpdates.emplace_back([=, this]()
            {
                if (m_states.contains(_id))
                {
                    const list<IGameState*>::iterator iter = std::find(m_activeStates.begin(), m_activeStates.end(), m_states[_id]);

                    if (iter == m_activeStates.end())
                    {
                        m_states[_id]->Load();
                        m_activeStates.push_back(m_states[_id]);
                    }
                }
            });
    }

    void GameStateManager::DeactivateState(const char* _id)
    {
        m_listUpdates.emplace_back([=, this]()
            {
                if (m_states.contains(_id))
                {
                    const list<IGameState*>::iterator iter = std::find(m_activeStates.begin(), m_activeStates.end(), m_states[_id]);

                    if (iter != m_activeStates.end())
                    {
                        (*iter)->Unload();
                        m_activeStates.erase(iter);
                    }
                }
            });
    }

    GameStateManager::~GameStateManager()
    {
        for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
            delete (*iter).second;

        m_states.clear();
        m_activeStates.clear();
    }

    void GameStateManager::Tick()
    {
        for (auto iter = m_listUpdates.begin(); iter != m_listUpdates.end(); ++iter)
            (*iter)();

        m_listUpdates.clear();

        for (auto iter = m_activeStates.begin(); iter != m_activeStates.end(); ++iter)
            (*iter)->Tick();
    }

    void GameStateManager::Render()
    {
        for (auto iter = m_activeStates.begin(); iter != m_activeStates.end(); ++iter)
            (*iter)->Render();
    }
}