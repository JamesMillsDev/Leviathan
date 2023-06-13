#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <Leviathan/Core/Object.h>
#include <Leviathan/Core/GameManagers.h>

#include <Leviathan/GameObjects/GameObject.h>
#include <Leviathan/GameObjects/GameObjectManager.h>
#include <Leviathan/GameObjects/TransformComponent.h>

namespace Leviathan
{
	class IGameState : public Object
	{
	public:
		virtual ~IGameState() = default;
		virtual void Load() = 0;
		virtual void Tick() {}
		virtual void Render() {}
		virtual void Unload() {}

	protected:
		IGameState(const char* _id) : m_name(_id)
		{
			m_world = new GameObject(string(_id) + " - World");
			GetObjectManager()->Spawn(m_world);
		}

		template<Derived<GameObject> GO>
		GO* CreateObject(const char* _name);

	private:
		friend class GameStateManager;

		GameObject* m_world;
		const char* m_name;

	};

	template<Derived<GameObject> GO>
	inline GO* IGameState::CreateObject(const char* _name)
	{
		GO* newObj = new GO();

		if (GameObject* go = dynamic_cast<GameObject*>(newObj))
		{
			go->SetName(_name);

			GetObjectManager()->Spawn(go);
			go->Transform()->SetParent(m_world->Transform());
		}

		return newObj;
	}

}