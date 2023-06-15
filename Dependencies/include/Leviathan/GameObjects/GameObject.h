#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Object.h>

#include <Leviathan/GameObjects/Component.h>
#include <Leviathan/GameObjects/TransformComponent.h>

#include <functional>
#include <list>
#include <map>
#include <string>
#include <vector>

using std::function;
using std::list;
using std::map;
using std::string;
using std::vector;

namespace Leviathan
{
	typedef function<void()> ComponentUpdateAction;
	typedef function<void(Component*, bool, Component*)> ComponentAddRemoveFunction;

	class GameObject : public Object
	{
	public:
		DLL GameObject();
		DLL GameObject(string _name);
		GameObject(GameObject&) = delete;
		DLL ~GameObject();

		DLL TObjectPtr<TransformComponent> Transform() const;

		DLL void SetName(string _name);
		DLL const string& GetName() const;

		DLL void SetTag(string _tag);
		DLL const string& GetTag() const;

		template<Derived<Component> COMPONENT>
		COMPONENT* GetComponent();

		template<Derived<Component> COMPONENT>
		COMPONENT* AddComponent();

		template<Derived<Component> COMPONENT>
		void DestroyComponent(COMPONENT* _component);

		const list<Component*> GetAllComponents() const;

		void ListenToAddRemoveComponent(ComponentAddRemoveFunction _callback, Component* _listener);
		void StopListeningToAddRemoveComponent(ComponentAddRemoveFunction _callback, Component* _listener);

	private:
		friend class GameObjectManager;

		TObjectPtr<TransformComponent> m_transform;

		vector<ComponentUpdateAction> m_listUpdates;
		map<Component*, ComponentAddRemoveFunction> m_addRemoveUpdates;
		list<Component*> m_components;

		string m_name;
		string m_tag;

	private:
		DLL void Load();
		DLL void Tick();
		DLL void Render();
		DLL void Unload();

		DLL void OnDrawGizmos();

	};

	template<Derived<Component> COMPONENT>
	COMPONENT* GameObject::GetComponent()
	{
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
		{
			if (COMPONENT* component = dynamic_cast<COMPONENT*>(*iter))
				return component;
		}

		return nullptr;
	}

	template<Derived<Component> COMPONENT>
	COMPONENT* GameObject::AddComponent()
	{
		if (typeid(COMPONENT) == typeid(TransformComponent))
			return nullptr;

		COMPONENT* component = new COMPONENT(this);

		m_listUpdates.push_back([=, this]()
			{
				component->Load();
				m_components.push_back(component);
				for (const auto& [caller, callback] : m_addRemoveUpdates)
					std::invoke(callback, component, true, caller);

			});

		return component;
	}

	template<Derived<Component> COMPONENT>
	void GameObject::DestroyComponent(COMPONENT* _component)
	{
		m_listUpdates.push_back([&, this]()
			{
				const list<Component*>::iterator iter = std::find(m_components.begin(), m_components.end(), _component);

				if (iter != m_components.end())
				{
					(*iter)->Unload();
					m_components.erase(iter, iter);

					for (const auto& [caller, callback] : m_addRemoveUpdates)
						std::invoke(callback, _component, false, caller);

					delete _component;
				}
			});
	}
}