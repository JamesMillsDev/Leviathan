#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"

#include <string>
#include <map>

#include <Leviathan/Math/Vec2.h>
#include <Leviathan/Math/Color32.h>

#include <type_traits>

using std::string;
using std::map;
using std::is_same;

typedef string group_id;

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
	static void reload();

	static int GetIntValue(string _group, string _id);
	static bool GetBooleanValue(string _group, string _id);
	static float GetFloatValue(string _group, string _id);
	static Vec2 GetVectorValue(string _group, string _id);
	static Color32 GetColorValue(string _group, string _id);
	static const char* GetTextValue(string _group, string _id);

	static void CreateInstance(string _filePath);
	static void DestroyInstance();

private:
	static Config* m_instance;

	string m_filePath;
	map<group_id, map<string, int>> m_intValues;
	map<group_id, map<string, bool>> m_boolValues;
	map<group_id, map<string, float>> m_floatValues;
	map<group_id, map<string, Vec2>> m_vectorValues;
	map<group_id, map<string, Color32>> m_colorValues;
	map<group_id, map<string, string>> m_textValues;

	Config(string _filePath);
	Config(const Config&) = delete;

	void Clear();
	void Load(string _filePath);

};