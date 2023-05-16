#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <Leviathan/Utils/Singleton.h>

#include <functional>
#include <list>
#include <vector>

using std::function;
using std::list;
using std::pair;
using std::vector;

class GameObjectManager final : public Singleton<GameObjectManager>
{
public:
	GameObjectManager() = default;
	GameObjectManager(GameObjectManager&) = delete;
	DLL ~GameObjectManager() override;

	DLL static void Spawn(class GameObject* _go);
	DLL static void Destroy(class GameObject* _go);

private:
	friend class Application;

	vector<pair<function<void(class GameObject*)>, class GameObject*>> m_listUpdates;
	list<class GameObject*> m_objects;

private:
	DLL static void Tick();
	DLL static void Render();

	DLL static void DrawGizmos();

};