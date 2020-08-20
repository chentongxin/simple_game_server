#pragma once

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { BUF_SIZE = 1024 };

class CSession : public std::enable_shared_from_this<CSession> {
public:
	CSession(tcp::socket socket) : m_socket(std::move(socket)) 
	{
	}

	void Start();
	void DoRead();
	void DoWrite();
private:
	tcp::socket m_socket;
	std::array<char, BUF_SIZE> m_buff;
};