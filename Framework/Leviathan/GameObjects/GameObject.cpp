#include <Leviathan/GameObjects/GameObject.h>

GameObject::GameObject() :
	m_name("Game Object"), m_tag("Default"), m_transform(new TransformComponent())
{
}

GameObject::GameObject(string _name) :
	m_name("Game Object"), m_tag("Default"), m_transform(new TransformComponent())

{
}

GameObject::~GameObject()
{
	while (m_components.size() > 0)
	{
		delete m_components.back();
		m_components.pop_back();
	}
}

DLL TransformComponent* GameObject::Transform()
{
	return m_transform;
}

void GameObject::Load()
{
	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Load();
	}
}

void GameObject::Tick()
{
	for (auto iter = m_listUpdates.begin(); iter != m_listUpdates.end(); iter++)
	{
		(*iter)();
	}

	m_listUpdates.clear();

	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Tick();
	}
}

void GameObject::Render()
{
	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Render();
	}
}

void GameObject::Unload()
{
	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Unload();
	}
}
