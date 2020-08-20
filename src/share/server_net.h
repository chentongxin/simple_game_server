#pragma once

#include "server_session.h"

class CServerNet 
{
public:
	CServerNet() :m_acceptor(nullptr)
	{
	
	}

	void Start(int port);
private:
	void DoAccept();
private:
	boost::asio::io_context m_ioc;
	tcp::acceptor* m_acceptor;
};