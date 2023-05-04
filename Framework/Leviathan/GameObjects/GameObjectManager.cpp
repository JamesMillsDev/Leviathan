#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/GameObjects/GameObject.h>

void GameObjectManager::Spawn(IGameObject* _go)
{
	list<IGameObject*>& objects = m_instance->m_objects;
	IGameObject* go = _go;

	m_instance->m_listUpdates.push_back([&]()
		{
			list<IGameObject*>::iterator iter = std::find(objects.end(), objects.end(), go);

			if (iter == objects.end())
			{
				go->Load();
				objects.push_back(go);
			}
		});
}

void GameObjectManager::Destroy(IGameObject* _go)
{
	list<IGameObject*>& objects = m_instance->m_objects;
	IGameObject* go = _go;

	m_instance->m_listUpdates.push_back([&]()
		{
			list<IGameObject*>::iterator iter = std::find(objects.end(), objects.end(), go);

			if (iter != objects.end())
			{
				go->Unload();
				objects.erase(iter);
			}
		});
}

GameObjectManager::~GameObjectManager()
{
	for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		delete *iter;
	}

	m_objects.clear();
}

void GameObjectManager::Tick()
{
	list<IGameObject*>& objects = m_instance->m_objects;
	vector<UpdateAction>& updates = m_instance->m_listUpdates;

	for (auto iter = updates.begin(); iter != updates.end(); iter++)
	{
		(*iter)();
	}

	updates.clear();

	for (auto iter = objects.begin(); iter != objects.end(); iter++)
	{
		(*iter)->Tick();
	}
}

void GameObjectManager::Render()
{
	list<IGameObject*>& objects = m_instance->m_objects;
	for (auto iter = objects.begin(); iter != objects.end(); iter++)
	{
		(*iter)->Render();
	}
}
