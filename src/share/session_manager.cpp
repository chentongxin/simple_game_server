#include "session_manager.h"

CSessionManager::CSessionManager()
{
	
}

void CSessionManager::Start(CSessionPtr c)
{
	m_sessions.insert(c);
	c->Start();
}

void CSessionManager::Stop(CSessionPtr c)
{
	m_sessions.erase(c);
	c->Stop();
}

void CSessionManager::Stop_all()
{
	  for (auto c: m_sessions)
		c->Stop();
	  m_sessions.clear();
}

void CSessionManager::Update()
{
	if (m_update_sessions.size() == 0)
	{
		m_update_sessions = m_sessions;
	}
	while (m_update_sessions.size()>0)
	{
		std::set<CSessionPtr>::iterator it = m_update_sessions.begin();
		if (it!=m_update_sessions.end())
		{
			(*it)->Update();
		}
		m_update_sessions.erase(it);
	}
}
