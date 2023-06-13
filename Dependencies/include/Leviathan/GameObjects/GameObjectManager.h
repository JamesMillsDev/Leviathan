#pragma once

#include <Leviathan/Core/Leviathan.h>

#include <functional>
#include <list>
#include <vector>

using std::function;
using std::list;
using std::pair;
using std::vector;

class GameObjectManager
{
public:
	GameObjectManager() = default;
	GameObjectManager(GameObjectManager&) = delete;
	DLL ~GameObjectManager();

	DLL void Spawn(class GameObject* _go);
	DLL void Destroy(class GameObject* _go);

private:
	friend class GameManagers;

	vector<pair<function<void(class GameObject*)>, class GameObject*>> m_listUpdates;
	list<class GameObject*> m_objects;

private:
	DLL void Tick();
	DLL void Render();

	DLL void DrawGizmos();

};