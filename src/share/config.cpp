#include "config.h"
#include "../share/logger.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

bool CConfig::ReadConfig(const std::string& module_path)
{
	return ReadServers(module_path);
}

std::string CConfig::GetServersConfig(const std::string server_name, const std::string key) const
{
	std::map<std::string, std::map<std::string, std::string> >::const_iterator it_server = m_servers_config.find(server_name);
	if (it_server == m_servers_config.end())
	{
		return "";
	}

	std::map<std::string, std::string>::const_iterator it = it_server->second.find(key);
	if (it == it_server->second.end())
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

	for (boost::property_tree::ptree::iterator it_root = root.begin(); it_root != root.end(); ++it_root)
	{
		boost::property_tree::ptree items = root.get_child(it_root->first);

		std::map<std::string, std::string> one_server;

		for (boost::property_tree::ptree::iterator it = items.begin(); it != items.end(); ++it)
		{
			if (it->first.length() <= 0)
			{
				LogError("CConfig::ReadServers empty key:", file_path);
				continue;
			}
			one_server.insert(std::make_pair(it->first, it->second.get_value<std::string>()));
		}
		m_servers_config.insert(std::make_pair(it_root->first, one_server));
	}



	LogInfo("CConfig::ReadServers read config success: servers.json");
	return true;
}

