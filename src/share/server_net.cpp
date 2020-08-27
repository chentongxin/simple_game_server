#include "server_net.h"
#include "logger.h"
#include <iostream>
#include "server_manager.h"

void CServerNet::Start(int port)
{
	m_update_timer.expires_from_now(std::chrono::milliseconds(500));
	m_update_timer.async_wait(std::bind(&CServerNet::Update, this));

	m_acceptor = new tcp::acceptor(m_ioc, tcp::endpoint(tcp::v4(), port));
	DoAccept();
	LogInfo("CServerNet Start on port:", port);
	m_ioc.run();
}

void CServerNet::Update()
{
	CServerManager::getInstance()->Update();

	m_session_manager.Update();

	m_update_timer.expires_from_now(std::chrono::milliseconds(500));
	m_update_timer.async_wait(std::bind(&CServerNet::Update, this));
}

void CServerNet::DoAccept()
{
	assert(m_acceptor);
	m_acceptor->async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
	{
		if (!ec)
		{
			//std::make_shared<CSession>(std::move(socket))->Start();
			m_session_manager.Start(std::make_shared<CSession>(std::move(socket)));
		}

		DoAccept();
	});
}

