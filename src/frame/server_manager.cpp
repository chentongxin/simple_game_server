#include <boost\filesystem.hpp>
#include <boost/lexical_cast.hpp> 

#include "server_manager.h"
#include "config.h"
#include "logger.h"

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

	//初始化日志库
	g_InitLog(debug, m_module_path, m_server_name);

	//读取配置
	bool ret = ReadConfig();
	if (!ret)
	{
		LogError("ReadConfig Error!");
		return false;
	}

	try {
		int log_level = boost::lexical_cast<int>(m_config->GetServersConfig("log_level"));
		//重新设置等级
		g_InitLog((SeverityLevel)log_level, m_module_path, m_server_name);
	}
	catch (boost::bad_lexical_cast& e) {
		std::string log_info = "CServerManager::Init:";
		LogError(log_info + e.what());
		return false;

	}

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
