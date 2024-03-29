#include <Leviathan/GameObjects/GameObject.h>

GameObject::GameObject() :
    m_transform(new TransformComponent()), m_name("Game Object"), m_tag("Default")
{
}

GameObject::GameObject(string _name) :
    m_transform(new TransformComponent()), m_name("Game Object"), m_tag("Default")
{
}

GameObject::~GameObject()
{
    while(!m_components.empty())
    {
        delete m_components.back();
        m_components.pop_back();
    }
}

DLL TransformComponent* GameObject::Transform() const
{
    return m_transform;
}

void GameObject::ListenToAddRemoveComponent(ComponentAddRemoveFunction _callback, Component* _listener)
{
    if(!m_addRemoveUpdates.contains(_listener))
        m_addRemoveUpdates[_listener] = _callback;
}

void GameObject::StopListeningToAddRemoveComponent(ComponentAddRemoveFunction _callback, Component* _listener)
{
    if(m_addRemoveUpdates.contains(_listener))
        m_addRemoveUpdates.erase(_listener);
}

void GameObject::Load()
{
    for(auto iter = m_components.begin(); iter != m_components.end(); ++iter)
        (*iter)->Load();
}

void GameObject::Tick()
{
    for(auto iter = m_listUpdates.begin(); iter != m_listUpdates.end(); ++iter)
        (*iter)();

    m_listUpdates.clear();

    for(auto iter = m_components.begin(); iter != m_components.end(); ++iter)
    {
        Component* component = *iter;
        if(component->IsEnabled())
            component->Tick();
    }
}

void GameObject::Render()
{
    for(auto iter = m_components.begin(); iter != m_components.end(); ++iter)
        (*iter)->Render();
}

void GameObject::Unload()
{
    for(auto iter = m_components.begin(); iter != m_components.end(); ++iter)
        (*iter)->Unload();
}

void GameObject::OnDrawGizmos()
{
    for(auto iter = m_components.begin(); iter != m_components.end(); iter++)
        (*iter)->OnDrawGizmos();
}
