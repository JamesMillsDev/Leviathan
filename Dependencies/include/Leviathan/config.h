#pragma once

#define PROGRAM_CATEGORY "Program"
#define WINDOW_CATEGORY "Window"
#define DEBUG_CATEGORY "Debug"

#include <string>
#include <map>

#include <Leviathan/Math/vec2.h>
#include <Leviathan/Math/color.h>

#include <type_traits>

using std::string;
using std::map;
using std::is_same;

typedef string group_id;

struct invalid_value_exception : public std::exception
{
	string value;

	invalid_value_exception(string _value) : value("Key not found: " + _value) {}

	const char* what() const throw ()
	{
		return value.c_str();
	}
};

class config
{
public:
	static void reload();


	static int getIntValue(string _group, string _id);
	static bool getBooleanValue(string _group, string _id);
	static float getFloatValue(string _group, string _id);
	static vec2 getVectorValue(string _group, string _id);
	static color getColorValue(string _group, string _id);
	static const char* getTextValue(string _group, string _id);

	static void createInstance(string _filePath);
	static void destroyInstance();

private:
	static config* m_instance;

	string m_filePath;
	map<group_id, map<string, int>> m_intValues;
	map<group_id, map<string, bool>> m_boolValues;
	map<group_id, map<string, float>> m_floatValues;
	map<group_id, map<string, vec2>> m_vectorValues;
	map<group_id, map<string, color>> m_colorValues;
	map<group_id, map<string, string>> m_textValues;

	config(string _filePath);
	config(const config&) = delete;

	void clear();
	void load(string _filePath);

};