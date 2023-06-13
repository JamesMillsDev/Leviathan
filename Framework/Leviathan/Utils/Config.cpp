#include <Leviathan/Utils/Config.h>

#include <Leviathan/Core/Application.h>
#include <Leviathan/Core/Color32.h>

#include <Leviathan/Utils/ConfigValue.h>

#include <glm/vec2.hpp>

#include <fstream>
#include <ranges>
#include <vector>

using glm::vec2;

using std::ifstream;
using std::vector;

using std::getline;

namespace Leviathan
{
	void Config::Reload()
	{
		Clear();
		Load(m_filePath);

		for (auto& iter : m_listeners)
			iter->Call();
	}

	Config::Config(const string& _filePath)
	{
		Application::AddConfigReloadCallback(&Config::Reload, this);

		m_filePath = "config\\" + _filePath;
		Load(m_filePath);
	}

	Config::~Config()
	{
		for (size_t i = 0; i < m_listeners.size(); i++)
		{
			delete m_listeners[i];
		}

		m_listeners.clear();

		for (auto& group : m_configValues)
		{
			for (auto& set : group.second)
			{
				delete set.second;
			}
		}

		m_configValues.clear();
	}

	ConfigValue* Config::GetValue(const string _group, const string _id)
	{
		if (m_configValues.contains(_group))
		{
			auto& set = m_configValues[_group];

			if (set.contains(_id))
			{
				return set[_id];
			}
		}

		return nullptr;
	}

	void Config::Clear()
	{
		for (auto& group : m_configValues | std::views::values)
		{
			for (auto iter = group.begin(); iter != group.end(); ++iter)
				delete (*iter).second;
		}

		m_configValues.clear();
	}

	void Config::Load(string _filePath)
	{
		ifstream configFile("assets\\" + _filePath);
		if (configFile.bad())
			throw R"(Config file missing)";

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
						m_configValues[lastGroup][id] = new ConfigValue(new vec2{ values[0], values[1] });
					}
					else if (values.size() == 4)
					{
						m_configValues[lastGroup][id] = new ConfigValue(new Color32
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
						m_configValues[lastGroup][id] = new ConfigValue(new float((float)atof(val.c_str())));
						continue;
					}

					if (val == "false" || val == "true")
					{
						m_configValues[lastGroup][id] = new ConfigValue(new bool(val == "true"));
					}
					else
					{
						int ascii = val[0];
						if (ascii >= 48 && ascii <= 57)
						{
							m_configValues[lastGroup][id] = new ConfigValue(new int(atoi(val.c_str())));
						}
						else
						{
							m_configValues[lastGroup][id] = new ConfigValue(new string(val));
						}
					}
				}
			}
		}

		configFile.close();
	}
}
