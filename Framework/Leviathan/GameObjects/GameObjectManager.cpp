#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/GameObjects/GameObject.h>

namespace Leviathan
{
    void GameObjectManager::Spawn(GameObject* _go)
    {
        m_listUpdates.emplace_back([&](GameObject* _g)
            {
                const list<GameObject*>::iterator iter = std::find(m_objects.end(), m_objects.end(), _g);

                if (iter == m_objects.end())
                {
                    _g->Load();
                    m_objects.push_back(_g);
                }
            }, _go);
    }

    void GameObjectManager::Destroy(GameObject* _go)
    {
        m_listUpdates.emplace_back([&](GameObject* _g)
            {
                const list<GameObject*>::iterator iter = std::find(m_objects.end(), m_objects.end(), _g);

                if (iter != m_objects.end())
                {
                    _g->Unload();
                    m_objects.erase(iter);
                    delete _g;
                }
            }, _go);
    }

    GameObjectManager::~GameObjectManager()
    {
        for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
            delete* iter;

        m_objects.clear();
    }

    void GameObjectManager::Tick()
    {
        for (auto iter = m_listUpdates.begin(); iter != m_listUpdates.end(); ++iter)
            (*iter).first((*iter).second);

        m_listUpdates.clear();

        for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
            (*iter)->Tick();
    }

    void GameObjectManager::Render()
    {
        for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
            (*iter)->Render();
    }

    void GameObjectManager::DrawGizmos()
    {
        for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
            (*iter)->OnDrawGizmos();
    }
}
