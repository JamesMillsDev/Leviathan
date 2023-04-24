#pragma once

#include <functional>
#include <vector>

using std::function;
using std::vector;

typedef function<void()> UpdateAction;

class GameObjectManager
{
public:
	void Spawn(class IGameObject* _go);
	void Destroy(class IGameObject* _go);

private:
	friend class Application;

	static GameObjectManager* m_instance;

	vector<UpdateAction> m_listUpdates;
	vector<class IGameObject*> m_objects;

	GameObjectManager() = default;
	GameObjectManager(GameObjectManager&) = delete;
	~GameObjectManager();

	static void CreateInstance();
	static void DestroyInstance();

	static void Tick();
	static void Render();

};