#pragma once

#include <Leviathan/Singleton.h>

#include <functional>
#include <vector>

using std::function;
using std::vector;

typedef function<void()> UpdateAction;

class GameObjectManager : Singleton<GameObjectManager>
{
public:
	void Spawn(class IGameObject* _go);
	void Destroy(class IGameObject* _go);

private:
	friend class Application;

	vector<UpdateAction> m_listUpdates;
	vector<class IGameObject*> m_objects;

	GameObjectManager() = default;
	GameObjectManager(GameObjectManager&) = delete;
	~GameObjectManager();

	static void Tick();
	static void Render();

};