#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"

#include <Leviathan/Leviathan.h>
#include <Leviathan/Math/Vec2.h>
#include <Leviathan/Math/Color32.h>

#include <string>
#include <map>
#include <vector>
#include <functional>

#include <type_traits>

using std::string;
using std::map;
using std::vector;
using std::function;
using std::is_same;

typedef string group_id;

typedef function<void(class Config*)> ConfigReloadCallback;

struct InvalidValueException : public std::exception
{
	string value;

	InvalidValueException(string _value) : value("Key not found: " + _value) {}

	const char* what() const throw ()
	{
		return value.c_str();
	}
};

class Config
{
public:
	DLL Config(string _filePath);

	template<typename DATA>
	DATA* GetValue(string _group, string _id);

	DLL void ListenForReload(ConfigReloadCallback _callback);

private:
	string m_filePath;
	map<group_id, map<string, void*>> m_data;
	vector<ConfigReloadCallback> m_listeners;

private:
	Config(const Config&) = delete;

	DLL void Reload();
	DLL void Clear();
	DLL void Load(string _filePath);

};

template<typename DATA>
inline DATA* Config::GetValue(string _group, string _id)
{
	if (m_data.find(_group) != m_data.end())
	{
		auto& set = m_data[_group];

		if (set.find(_id) != set.end())
		{
			return (DATA*)set[_id];
		}
	}

	return nullptr;
}
