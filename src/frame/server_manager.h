#pragma once
#include <string>

class CConfig;
class CServerNet;

class CServerManager {
public:
	static CServerManager* getInstance();

	bool Init(std::string name);
	bool Start();

	bool ReadConfig();
	const std::string& GetModulePath() const;
private:
	static CServerManager* instance;
	CServerManager();

	std::string m_module_path;
	std::string m_server_name;

	CConfig* m_config;
	CServerNet* m_net;
};