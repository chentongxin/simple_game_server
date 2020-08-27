#pragma once

#include <set>
#include "server_session.h"

class CSessionManager
{
public:
	CSessionManager(const CSessionManager&) = delete;
	CSessionManager& operator=(const CSessionManager&) = delete;
	CSessionManager();

  void Start(CSessionPtr c);

  void Stop(CSessionPtr c);

  void Stop_all();

  void Update();
private:
  std::set<CSessionPtr> m_sessions;
  std::set<CSessionPtr> m_update_sessions;
};