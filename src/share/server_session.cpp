#include "server_session.h"
#include <iostream>
#include "header.hpp"

CSession::~CSession()
{
	std::cout << "~CSession" << std::endl;
}

void CSession::Start()
{
	DoRead();
}

void CSession::Stop()
{
	m_socket.close();
}

void CSession::DoRead()
{
	auto self(shared_from_this());
	m_socket.async_read_some(boost::asio::buffer(m_buff, BUF_SIZE),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			//DoWrite();
			server::event_ptr ev = std::make_shared<server::event>();
			ev->m_content = std::string(m_buff.data(), m_buff.data() + length);
			SendEvent(ev);
			//DoWriteTemp();
			std::cout << "read:" << length << std::endl;
		}
		DoRead();
	});
}

void CSession::DoWrite()
{
	std::cout << "DoWrite" << std::endl;
	auto self(shared_from_this());
	while (!m_write_events.empty())
	{
		server::event_ptr ep = m_write_events.front();
		m_write_events.pop_front();

		boost::asio::write(m_socket, ep->to_buffers());
	}
	
}

void CSession::DoWriteTemp()
{
	auto self(shared_from_this());
	boost::asio::async_write(m_socket, boost::asio::buffer(m_buff, BUF_SIZE),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			std::cout << "write:" << length << std::endl;
		}
	});
}

void CSession::SendEvent(server::event_ptr& ev)
{
	std::cout << "SendEvent" << std::endl;
	m_write_events.push_back(ev);
}

void CSession::Update()
{
	DoWrite();
}
