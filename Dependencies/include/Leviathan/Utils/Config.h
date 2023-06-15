#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"

#include <Leviathan/Leviathan.h>
#include <Leviathan/Callback.h>

#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

using std::is_same;
using std::map;
using std::string;
using std::vector;

namespace Leviathan
{
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
		DLL Config(const string& _filePath);
		DLL ~Config();

		class ConfigValue* GetValue(string _group, string _id);

		template<typename T>
		void ListenForReload(void(T::* _callback)(Config*), T* _owner);

	private:
		string m_filePath;
		map<string, map<string, class ConfigValue*>> m_configValues;
		vector<Callback*> m_listeners;

	private:
		Config(const Config&) = delete;

		DLL void Reload();
		DLL void Clear();
		DLL void Load(string _filePath);

	};

	template<typename T>
	inline void Config::ListenForReload(void(T::* _callback)(Config*), T* _owner)
	{
		TemplateCallbackOneParam<T, Config>* callback = new TemplateCallbackOneParam<T, Config>();
		callback->callback = _callback;
		callback->owner = _owner;
		callback->param0 = this;

		m_listeners.push_back(callback);
	}
}