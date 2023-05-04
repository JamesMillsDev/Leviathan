#include <Leviathan/GameObjects/GameObject.h>

IGameObject::IGameObject() :
	m_name("Game Object"), m_tag("Default"), m_transform(new TransformComponent())
{
}

IGameObject::IGameObject(string _name) :
	m_name("Game Object"), m_tag("Default"), m_transform(new TransformComponent())

{
}

IGameObject::~IGameObject()
{
	while (m_components.size() > 0)
	{
		delete m_components.back();
		m_components.pop_back();
	}
}

DLL TransformComponent* IGameObject::Transform()
{
	return m_transform;
}

void IGameObject::Load()
{
	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Load();
	}
}

void IGameObject::Tick()
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

void IGameObject::Render()
{
	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Render();
	}
}

void IGameObject::Unload()
{
	for (auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		(*iter)->Unload();
	}
}
