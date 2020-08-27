//
// connection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include <iostream>

namespace server {


	connection::~connection()
	{
		std::cout << "~connection" << std::endl;
	}

connection::connection(boost::asio::ip::tcp::socket socket,
    connection_manager& manager, request_handler& handler)
  : socket_(std::move(socket)),
    connection_manager_(manager),
    request_handler_(handler)
{
}

void connection::start()
{
  do_read();
}

void connection::stop()
{
  socket_.close();
}

void connection::do_read()
{
	std::cout << "do_read====" << std::endl;
  auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(buffer_),
		[this, self](boost::system::error_code ec, std::size_t bytes_transferred)
	{
		if (!ec)
		{
			std::string temp = std::string(buffer_.data(), buffer_.data() + bytes_transferred);
			std::cout << temp << std::endl;
			request_parser::result_type result;
			char* content_char = nullptr;
			std::tie(result, content_char) = request_parser_.parse(
				request_, buffer_.data(), buffer_.data() + bytes_transferred);

			if (result == request_parser::good)
			{
				request_handler_.handle_request(request_, reply_);
				request_parser_.reset();
				request_.Clear();
				do_write();
			}
			else if (result == request_parser::bad)
			{
				reply_ = reply::stock_reply(reply::bad_request);
				request_parser_.reset();
				request_.Clear();
				do_write();
			}
		}
		else if (ec == boost::asio::error::operation_aborted)
		{
			connection_manager_.stop(shared_from_this());
		}
		std::cout << "read finish:" << ec << std::endl;
		do_read();
	});
	std::cout << "read finish====" << std::endl;
}

void connection::do_write()
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_, reply_.to_buffers(),
      [this, self](boost::system::error_code ec, std::size_t)
      {
	 
        if (!ec)
        {
			
			return;
          // Initiate graceful connection closure.
          boost::system::error_code ignored_ec;
          socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted)
        {
          connection_manager_.stop(shared_from_this());
        }
      });
}

} // namespace server
