#pragma once

#include <map>

class CConfig {
public:
	bool ReadConfig(const std::string& module_path);
	std::string GetServersConfig(const std::string key) const;

private:
	bool ReadServers(const std::string& module_path);

	std::map<std::string, std::string> m_servers_config;
};