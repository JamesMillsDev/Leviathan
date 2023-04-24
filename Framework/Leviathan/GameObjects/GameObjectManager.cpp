#include <Leviathan/GameObjects/GameObjectManager.h>

#include <Leviathan/GameObjects/GameObject.h>

GameObjectManager* GameObjectManager::m_instance = nullptr;

void GameObjectManager::Spawn(IGameObject* _go)
{
	vector<IGameObject*>& objects = m_instance->m_objects;

	m_instance->m_listUpdates.push_back([&]()
		{
			vector<IGameObject*>::iterator iter = std::find(objects.end(), objects.end(), _go);

			if (iter == objects.end())
			{
				_go->Load();
				objects.push_back(_go);
			}
		});
}

void GameObjectManager::Destroy(IGameObject* _go)
{
	vector<IGameObject*>& objects = m_instance->m_objects;

	m_instance->m_listUpdates.push_back([&]()
		{
			vector<IGameObject*>::iterator iter = std::find(objects.end(), objects.end(), _go);

			if (iter != objects.end())
			{
				_go->Unload();
				objects.erase(iter, iter);
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
	vector<IGameObject*>& objects = m_instance->m_objects;
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
	vector<IGameObject*>& objects = m_instance->m_objects;
	for (auto iter = objects.begin(); iter != objects.end(); iter++)
	{
		(*iter)->Render();
	}
}
