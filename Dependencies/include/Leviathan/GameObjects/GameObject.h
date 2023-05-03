#pragma once

#include <concepts>
#include <functional>
#include <vector>
#include <string>

#include <Leviathan/Leviathan.h>
#include <Leviathan/GameObjects/Component.h>
#include <Leviathan/GameObjects/TransformComponent.h>

using std::function;
using std::vector;
using std::string;

typedef function<void()> UpdateAction;

class IGameObject
{
public:
	template<Derived<IComponent> COMPONENT>
	COMPONENT* GetComponent();

	template<Derived<IComponent> COMPONENT>
	COMPONENT* AddComponent();

	template<Derived<IComponent> COMPONENT>
	void DestroyComponent(COMPONENT* _component);

private:
	friend class GameObjectManager;

	TransformComponent* m_transform;

	vector<UpdateAction> m_listUpdates;
	vector<IComponent*> m_components;

	string m_name;
	string m_tag;

private:
	DLL IGameObject();
	DLL IGameObject(string _name);
	IGameObject(IGameObject&) = delete;
	DLL ~IGameObject();

	DLL void Load();
	DLL void Tick();
	DLL void Render();
	DLL void Unload();

};

template<Derived<IComponent> COMPONENT>
inline COMPONENT* IGameObject::GetComponent()
{
	for(auto iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		if (COMPONENT* component = dynamic_cast<COMPONENT*>(*iter))
		{
			return component;
		}
	}

	return nullptr;
}

template<Derived<IComponent> COMPONENT>
inline COMPONENT* IGameObject::AddComponent()
{
	if (typeid(COMPONENT) == typeid(TransformComponent))
		return;

	COMPONENT* component = new COMPONENT(this);

	m_listUpdates.push_back([&]()
		{
			component->Load();
			m_components.push_back(component);
		});

	return component;
}

template<Derived<IComponent> COMPONENT>
inline void IGameObject::DestroyComponent(COMPONENT* _component)
{
	m_listUpdates.push_back([&, this]()
		{
			vector<IComponent*>::iterator iter = std::find(m_components.begin(), m_components.end(), _component);

			if (iter != m_components.end())
			{
				(*iter)->Unload();
				m_components.erase(iter, iter);
			}
		});
}
