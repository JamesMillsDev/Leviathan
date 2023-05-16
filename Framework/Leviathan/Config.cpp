#include <Leviathan/Config.h>

#include <Leviathan/Application.h>
#include <Leviathan/Color32.h>
#include <Leviathan/ConfigValue.h>

#include <glm/vec2.hpp>

#include <fstream>
#include <vector>

using glm::vec2;

using std::ifstream;
using std::vector;

using std::getline;

void Config::Reload()
{
	Clear();
	Load(m_filePath);

	for (auto& iter : m_listeners)
		iter(this);
}

Config::Config(string _filePath)
{
	Application::AddConfigReloadCallback(&Config::Reload, this);

	m_filePath = _filePath;
	Load(m_filePath);
}

class ConfigValue* Config::GetValue(string _group, string _id)
{
	if (m_data.find(_group) != m_data.end())
	{
		auto& set = m_data[_group];

		if (set.find(_id) != set.end())
		{
			return (ConfigValue*)set[_id];
		}
	}

	return nullptr;
}

void Config::ListenForReload(ConfigReloadCallback _callback)
{
	m_listeners.push_back(_callback);
}

void Config::Clear()
{
	for (auto group : m_data)
	{
		for (auto iter = group.second.begin(); iter != group.second.end(); iter++)
		{
			delete (*iter).second;
		}
	}

	m_data.clear();
}

void Config::Load(string _filePath)
{
	ifstream configFile("assets\\" + _filePath);
	if (configFile.bad())
		throw "Config file missing";

	string line;
	string lastGroup;

	while (getline(configFile, line))
	{
		if (line.length() == 0 || line[0] == '#')
			continue;

		if (line[0] == '[')
		{
			string newLine = line;
			newLine.erase(0, 1);
			newLine.erase(newLine.end() - 1, newLine.end());
			lastGroup = newLine;
		}
		else
		{
			string id = line;
			size_t index = line.find_first_of('=');
			id.erase(index, id.length() - index);

			string val = line;
			val.erase(0, index + 1);

			if (val.find(',') != -1)
			{
				// color / vector
				string token;
				string delim = ",";
				string s = val;

				vector<float> values;
				size_t pos = 0;
				while ((pos = s.find(delim)) != string::npos)
				{
					token = s.substr(0, pos);
					values.push_back(std::stof(token));
					s.erase(0, pos + delim.length());
				}

				values.push_back(std::stof(s));

				if (values.size() == 2)
				{
					m_data[lastGroup][id] = new ConfigValue(new vec2{ values[0], values[1] });
				}
				else if (values.size() == 4)
				{
					m_data[lastGroup][id] = new ConfigValue(new Color32
					{
						(uint8_t)values[0],
						(uint8_t)values[1],
						(uint8_t)values[2],
						(uint8_t)values[3]
					});
				}
			}
			else
			{
				if (val.find('.') != -1)
				{
					m_data[lastGroup][id] = new ConfigValue(new float((float)atof(val.c_str())));
					continue;
				}

				if (val == "false" || val == "true")
				{
					m_data[lastGroup][id] = new ConfigValue(new bool(val == "true"));
				}
				else
				{
					int ascii = (int)val[0];
					if (ascii >= 48 && ascii <= 57)
					{
						m_data[lastGroup][id] = new ConfigValue(new int(atoi(val.c_str())));
					}
					else
					{
						m_data[lastGroup][id] = new ConfigValue(new string(val));
					}
				}
			}
		}
	}

	configFile.close();
}
