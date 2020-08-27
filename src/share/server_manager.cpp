#include <boost/filesystem.hpp>

#include "server_manager.h"
#include "config.h"
#include "../share/logger.h"
#include "../share/server_net.h"
#include "../share/util.h"

CServerManager* CServerManager::instance = nullptr;

CServerManager::CServerManager()
{
	m_module_path = boost::filesystem::initial_path<boost::filesystem::path>().string();
	m_config = new CConfig();
}

CServerManager* CServerManager::getInstance()
{
	if (instance == nullptr) {
		instance = new CServerManager();
	}
	return instance;
}

bool CServerManager::Init(std::string name)
{
	assert(m_config);

	m_server_name = name;

#ifdef _WINDOWS_
	SetConsoleTitle(m_server_name.c_str());
#endif // _WINDOWS_

	//��ʼ����־��
	g_InitLog(debug, m_module_path, m_server_name);

	//��ȡ����
	bool ret = ReadConfig();
	if (!ret)
	{
		LogError("ReadConfig Error!");
		return false;
	}

	std::string str_log_level = m_config->GetServersConfig(m_server_name, "log_level");
	int log_level = 0;
	if (!SimpleUtil::SToI(str_log_level, log_level))
	{
		LogError("CServerManager::Init log_level error:", str_log_level);
		return false;
	}
	
	
	g_SetLevel(log_level);
	LogDebug("CServerManager Init debug log_level:", log_level);
	LogInfo("CServerManager Init  info log_level:", log_level);
	LogError("CServerManager Init  error log_level:", log_level);

	LogInfo("CServerManager Init success!");
	return true;
}

bool CServerManager::Start()
{

	std::string str_ip = m_config->GetServersConfig(m_server_name, "ip");
	std::string str_port = m_config->GetServersConfig(m_server_name, "port");
	int port = 0;
	if (!SimpleUtil::SToI(str_port, port))
	{
		LogError("CServerManager::Init port error:", str_port);
		return false;
	}

	//m_server = new server::server(str_ip, str_port);

	//if (m_server == nullptr)
	//{
	//	LogInfo("CServerManager Start failed! new server null.");
	//}

	//LogInfo("CServerManager Start Success! on:", str_ip, ":", str_port);

	//m_server->run();

	m_net = new CServerNet();
	m_net->Start(port);

	return true;
}

bool CServerManager::Stop()
{
	return true;
}

bool CServerManager::ReadConfig()
{
	if (m_config == nullptr)
	{
		return false;
	}
	return m_config->ReadConfig(m_module_path);
}

const std::string& CServerManager::GetModulePath() const
{
	return m_module_path;
}

void CServerManager::Update()
{

}
