#include <Leviathan/Resources/Resources.h>

#include <Leviathan/Core/Application.h>

#include <filesystem>
#include <iostream>

using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::is_directory;
using std::filesystem::exists;

namespace Leviathan
{
	string Resources::PathFromID(const string& _id)
	{
		if (m_instance->m_paths.contains(_id))
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
		for (auto iter = m_resources.begin(); iter != m_resources.end(); ++iter)
			delete (*iter).second;

		m_resources.clear();
	}

	void Resources::LocateFiles(const string _path, const string _extension)
	{
		const path dir = path(string(Application::GetApplicationDirectory()) + "\\assets\\" + _path);
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

	bool Resources::HasResource(const string& _id) const
	{
		return m_resources.contains(_id);
	}

	Resources* Resources::GetInstance()
	{
		return m_instance;
	}
}
