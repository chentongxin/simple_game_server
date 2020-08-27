#pragma once

#include "server_session.h"
#include <boost/asio/high_resolution_timer.hpp >
#include <boost/asio/steady_timer.hpp >
#include <boost/asio/system_timer.hpp >
#include "session_manager.h"

class CServerNet 
{
public:
	CServerNet() 
		:m_acceptor(nullptr),
		m_update_timer(m_ioc)
	{
	
	}

	void Start(int port);

	void Update();
private:
	void DoAccept();
private:
	boost::asio::io_context m_ioc;
	tcp::acceptor* m_acceptor;
	boost::asio::steady_timer m_update_timer;

	CSessionManager m_session_manager;
};