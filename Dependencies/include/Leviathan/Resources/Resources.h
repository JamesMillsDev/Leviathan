#pragma once

#include <Leviathan/Leviathan.h>
#include <Leviathan/Singleton.h>
#include <Leviathan/Resources/Resource.h>

#include <map>
#include <string>

using std::string;
using std::map;

class Resources : public Singleton<Resources>
{
public:
	template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
	static RESOURCE* Find(string _id);

	DLL virtual void OnCreate() override;
	DLL virtual void OnDestroy() override;

protected:
	DLL static string PathFromID(string& _id);

private:
	map<string, string> m_paths;
	map<string, void*> m_resources;

	template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
	static RESOURCE* TryGetResource(string& _id);

	DLL void LocateFiles(string _path, string _extensions);
	DLL bool HasResource(string& _id);

	DLL static Resources* GetInstance();

};

template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
RESOURCE* Resources::Find(string _id)
{
	return dynamic_cast<RESOURCE*>(TryGetResource<ASSET, RESOURCE>(_id));
}

template<typename ASSET, Derived<Resource<ASSET>> RESOURCE>
RESOURCE* Resources::TryGetResource(string& _id)
{
	string path = PathFromID(_id);
	if (!path.empty())
	{
		if (!GetInstance()->HasResource(_id))
		{
			GetInstance()->m_resources[_id] = new RESOURCE(path);
		}

		return (RESOURCE*)GetInstance()->m_resources[_id];
	}

	return nullptr;
}
