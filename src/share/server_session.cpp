#include "server_session.h"
#include <iostream>

void CSession::Start()
{
	DoRead();
}

void CSession::DoRead()
{
	auto self(shared_from_this());
	m_socket.async_read_some(boost::asio::buffer(m_buff, BUF_SIZE),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			DoWrite();
		}
		DoRead();
	});
}

void CSession::DoWrite()
{
	auto self(shared_from_this());
	boost::asio::async_write(m_socket, boost::asio::buffer(m_buff, BUF_SIZE),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			
		}
	});
}
