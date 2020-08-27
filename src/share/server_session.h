#pragma once

#include <memory>
#include "header.hpp"
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

enum { BUF_SIZE = 1024 };

class CSession : public std::enable_shared_from_this<CSession> {
public:
	CSession(tcp::socket socket) : m_socket(std::move(socket)) 
	{

	}
	~CSession();

	void Start();
	void Stop();
	void DoRead();
	void DoWrite();
	void DoWriteTemp();

	void SendEvent(server::event_ptr& ev);

	void Update();
private:
	tcp::socket m_socket;
	std::array<char, BUF_SIZE> m_buff;
	std::array<char, 512> m_send_buff;
	server::event_ptr m_cur_recieve_event;
	server::event_ptr m_cur_write_event;
	std::list<server::event_ptr> m_recv_events;
	std::list<server::event_ptr> m_write_events;
};

typedef std::shared_ptr<CSession> CSessionPtr;