#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/GameObjects/GameObject.h>

void GameObjectManager::Spawn(GameObject* _go)
{
    list<GameObject*>& objects = m_instance->m_objects;

    m_instance->m_listUpdates.emplace_back([&](GameObject* _g)
    {
        const list<GameObject*>::iterator iter = std::find(objects.end(), objects.end(), _g);

        if(iter == objects.end())
        {
            _g->Load();
            objects.push_back(_g);
        }
    }, _go);
}

void GameObjectManager::Destroy(GameObject* _go)
{
    list<GameObject*>& objects = m_instance->m_objects;

    m_instance->m_listUpdates.emplace_back([&](GameObject* _g)
    {
        const list<GameObject*>::iterator iter = std::find(objects.end(), objects.end(), _g);

        if(iter != objects.end())
        {
            _g->Unload();
            objects.erase(iter);
            delete _g;
        }
    }, _go);
}

GameObjectManager::~GameObjectManager()
{
    for(auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
        delete*iter;

    m_objects.clear();
}

void GameObjectManager::Tick()
{
    list<GameObject*>& objects = m_instance->m_objects;
    vector<pair<function<void(class GameObject*)>, GameObject*>>& updates = m_instance->m_listUpdates;

    for(auto iter = updates.begin(); iter != updates.end(); ++iter)
        (*iter).first((*iter).second);

    updates.clear();

    for(auto iter = objects.begin(); iter != objects.end(); ++iter)
        (*iter)->Tick();
}

void GameObjectManager::Render()
{
    list<GameObject*>& objects = m_instance->m_objects;

    for(auto iter = objects.begin(); iter != objects.end(); ++iter)
        (*iter)->Render();
}

void GameObjectManager::DrawGizmos()
{
    list<GameObject*>& objects = m_instance->m_objects;

    for(auto iter = objects.begin(); iter != objects.end(); ++iter)
        (*iter)->OnDrawGizmos();
}
