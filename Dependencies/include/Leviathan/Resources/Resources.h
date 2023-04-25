#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Singleton.h>
#include <Leviathan/Resources/Resource.h>

#include <map>
#include <string>
#include <concepts>

using std::string;
using std::map;

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class Resources : Singleton<Resources>
{
public:
	template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
	static RESOURCE* Find(string _id);

protected:
	DLL static string PathFromID(string& _id, map<string, string>& _paths);

	DLL virtual void OnCreate() override;
	DLL virtual void OnDestroy() override;

private:
	map<string, string> m_paths;
	map<string, string> m_resources;

	template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
	static RESOURCE* TryGetResource(string& _id, map<string, string>& _paths, map<string, void*>& _resources);

	DLL void LocateFiles(string& _path, string& _extensions);
	DLL bool HasResource(string& _id);

};

template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
inline RESOURCE* Resources::Find(string _id)
{
	map<string, string>& paths = m_instance->m_paths;
	map<string, void*>& resources = m_instance->m_resources;

	return dynamic_cast<RESOURCE*>(TryGetResource(_id, paths, resources));
}

template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
inline RESOURCE* Resources::TryGetResource(string& _id, map<string, string>& _paths, map<string, void*>& _resources)
{
	string path = PathFromID(_id, _paths);
	if (!path.empty())
	{
		if (!m_instance->HasResource(_id))
		{
			_resources[_id] = new RESOURCE(path);
		}

		return dynamic_cast<RESOURCE*>(_resources[_id]);
	}

	return nullptr;
}
