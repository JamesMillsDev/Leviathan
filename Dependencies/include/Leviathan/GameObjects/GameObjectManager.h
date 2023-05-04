#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Singleton.h>

#include <functional>
#include <vector>
#include <list>

using std::function;
using std::vector;
using std::list;

typedef function<void()> UpdateAction;

class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	GameObjectManager() = default;
	GameObjectManager(GameObjectManager&) = delete;
	DLL ~GameObjectManager();

	DLL static void Spawn(class IGameObject* _go);
	DLL static void Destroy(class IGameObject* _go);

private:
	friend class Application;

	vector<UpdateAction> m_listUpdates;
	list<class IGameObject*> m_objects;

private:
	DLL static void Tick();
	DLL static void Render();

};