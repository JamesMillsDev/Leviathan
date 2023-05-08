#pragma once

#include <concepts>
#include <functional>
#include <vector>
#include <list>
#include <string>

#include <Leviathan/Leviathan.h>
#include <Leviathan/GameObjects/Component.h>
#include <Leviathan/GameObjects/TransformComponent.h>

using std::function;
using std::vector;
using std::list;
using std::string;

typedef function<void()> ComponentUpdateAction;

class GameObject
{
public:
	DLL GameObject();
	DLL GameObject(string _name);
	GameObject(GameObject&) = delete;
	DLL ~GameObject();

	DLL TransformComponent* Transform();

	template<Derived<Component> COMPONENT>
	COMPONENT* GetComponent();

	template<Derived<Component> COMPONENT>
	COMPONENT* AddComponent();

	template<Derived<Component> COMPONENT>
	void DestroyComponent(COMPONENT* _component);

private:
	friend class GameObjectManager;

	TransformComponent* m_transform;

	vector<ComponentUpdateAction> m_listUpdates;
	list<Component*> m_components;

	string m_name;
	string m_tag;

private:

	DLL void Load();
	DLL void Tick();
	DLL void Render();
	DLL void Unload();

};

template<Derived<Component> COMPONENT>
inline COMPONENT* GameObject::GetComponent()
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

template<Derived<Component> COMPONENT>
inline COMPONENT* GameObject::AddComponent()
{
	if (typeid(COMPONENT) == typeid(TransformComponent))
		return nullptr;

	COMPONENT* component = new COMPONENT(this);

	m_listUpdates.push_back([=, this]()
		{
			component->Load();
			m_components.push_back(component);
		});

	return component;
}

template<Derived<Component> COMPONENT>
inline void GameObject::DestroyComponent(COMPONENT* _component)
{
	m_listUpdates.push_back([&, this]()
		{
			vector<Component*>::iterator iter = std::find(m_components.begin(), m_components.end(), _component);

			if (iter != m_components.end())
			{
				(*iter)->Unload();
				m_components.erase(iter, iter);
			}
		});
}
