#include "server_net.h"
#include "logger.h"

void CServerNet::Start(int port)
{
	m_acceptor = new tcp::acceptor(m_ioc, tcp::endpoint(tcp::v4(), port));
	DoAccept();
	LogInfo("CServerNet Start on port:", port);
	m_ioc.run();
}

void CServerNet::DoAccept()
{
	assert(m_acceptor);
	m_acceptor->async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
	{
		if (!ec)
		{
			std::make_shared<CSession>(std::move(socket))->Start();
		}

		DoAccept();
	});
}

