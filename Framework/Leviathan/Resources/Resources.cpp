#include <Leviathan/Resources/Resources.h>

#include <Leviathan/Application.h>

#include <filesystem>
#include <iostream>

using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::is_directory;
using std::filesystem::current_path;
using std::filesystem::exists;

string Resources::PathFromID(string& _id)
{
	if (m_instance->m_paths.find(_id) != m_instance->m_paths.end())
		return m_instance->m_paths[_id];

	return "";
}

void Resources::OnCreate()
{
	LocateFiles("textures", ".png");
	LocateFiles("textures", ".jpg");
	LocateFiles("images", ".png");
	LocateFiles("sounds", ".wav");
	LocateFiles("sounds", ".ogg");
	LocateFiles("fonts", ".ttf");
}

void Resources::OnDestroy()
{
	for (auto iter = m_resources.begin(); iter != m_resources.end(); iter++)
	{
		delete (*iter).second;
	}

	m_resources.clear();
}

void Resources::LocateFiles(string _path, string _extension)
{
	path dir = path(string(Application::GetApplicationDirectory()) + "\\assets\\" + _path);
	if (!exists(dir))
		return;

	for (recursive_directory_iterator i(dir), end; i != end; ++i)
	{
		if (!is_directory(i->path()))
		{
			if (i->path().extension() == _extension)
			{
				string fileName = i->path().filename().string();

				string id = _path + "/" + fileName.substr(0, fileName.find_last_of('.'));

				m_paths[id] = i->path().string();
			}
		}
	}
}

bool Resources::HasResource(string& _id)
{
	return m_resources.find(_id) != m_resources.end();
}

DLL Resources* Resources::GetInstance()
{
	return m_instance;
}
