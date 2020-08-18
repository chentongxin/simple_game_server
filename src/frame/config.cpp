#include "config.h"
#include "logger.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

bool CConfig::ReadConfig(const std::string& module_path)
{
	return ReadServers(module_path);
}

std::string CConfig::GetServersConfig(const std::string key) const
{
	std::map<std::string, std::string>::const_iterator it = m_servers_config.find(key);
	if (it == m_servers_config.end())
	{
		return "";
	}
	return it->second;
}

bool CConfig::ReadServers(const std::string& module_path)
{
	m_servers_config.clear();

	std::string file_path = module_path + "/../config/servers.json";
	boost::property_tree::ptree root;
	boost::property_tree::read_json<boost::property_tree::ptree>(file_path, root);

	boost::property_tree::ptree items = root.get_child("game");
	for (boost::property_tree::ptree::iterator it = items.begin(); it != items.end(); ++it)
	{
		if (it->first.length() <= 0)
		{
			LogError("empty key" + file_path);
			continue;
		}
		m_servers_config.insert(std::make_pair(it->first, it->second.get_value<std::string>()));
	}

	LogInfo("read config:" + file_path);
	return true;
}

