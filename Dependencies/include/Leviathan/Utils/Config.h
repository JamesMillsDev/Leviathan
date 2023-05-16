#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"

#include <Leviathan/Core/Leviathan.h>

#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

using std::function;
using std::is_same;
using std::map;
using std::string;
using std::vector;

typedef string GroupId;

typedef function<void(class Config*)> ConfigReloadCallback;

struct InvalidValueException final : std::exception
{
	string value;

	InvalidValueException(const string _value) : value("Key not found: " + _value) {}

	const char* what() const noexcept override
	{
		return value.c_str();
	}
};

class Config
{
public:
	DLL Config(string _filePath);

	class ConfigValue* GetValue(string _group, string _id);

	DLL void ListenForReload(ConfigReloadCallback _callback);

private:
	string m_filePath;
	map<GroupId, map<string, class ConfigValue*>> m_data;
	vector<ConfigReloadCallback> m_listeners;

private:
	Config(const Config&) = delete;

	DLL void Reload();
	DLL void Clear();
	DLL void Load(string _filePath);

};
