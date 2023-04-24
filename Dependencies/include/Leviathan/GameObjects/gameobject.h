#pragma once

#include <concepts>
#include <functional>
#include <vector>
#include <string>

#include <Leviathan/GameObjects/Component.h>
#include <Leviathan/GameObjects/Transform.h>

using std::function;
using std::vector;
using std::string;

typedef function<void()> UpdateAction;

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

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

	Transform* m_transform;

	vector<UpdateAction> m_listUpdates;
	vector<IComponent*> m_components;

	string m_name;
	string m_tag;

	IGameObject();
	IGameObject(string _name);
	IGameObject(IGameObject&) = delete;
	~IGameObject();

	void Load();
	void Tick();
	void Render();
	void Unload();

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
