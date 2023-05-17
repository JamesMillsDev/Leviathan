#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"

#include <Leviathan/Core/Leviathan.h>
#include <Leviathan/Core/Callback.h>

#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

using std::is_same;
using std::map;
using std::string;
using std::vector;

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
	DLL ~Config();

	class ConfigValue* GetValue(string _group, string _id);

	template<typename T>
	void ListenForReload(void(T::* _callback)(Config*), T* _owner);

private:
	template<typename T>
	struct TemplateCallback : public Callback
	{
	public:
		void(T::* callback)(Config*);
		T* owner;

		void Call() override;

	private:
		friend class Config;

		Config* m_config;

	};

private:
	string m_filePath;
	map<string, map<string, class ConfigValue*>> m_data;
	vector<Callback*> m_listeners;

private:
	Config(const Config&) = delete;

	DLL void Reload();
	DLL void Clear();
	DLL void Load(string _filePath);

};

template<typename T>
inline void Config::TemplateCallback<T>::Call()
{
	(owner->*callback)(m_config);
}

template<typename T>
inline void Config::ListenForReload(void(T::* _callback)(Config*), T* _owner)
{
	TemplateCallback<T>* callback = new TemplateCallback<T>();
	callback->callback = _callback;
	callback->owner = _owner;
	callback->m_config = this;

	m_listeners.push_back(callback);
}
