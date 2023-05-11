#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Singleton.h>

#include <functional>
#include <vector>
#include <list>

using std::function;
using std::vector;
using std::list;
using std::pair;

class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	GameObjectManager() = default;
	GameObjectManager(GameObjectManager&) = delete;
	DLL ~GameObjectManager();

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