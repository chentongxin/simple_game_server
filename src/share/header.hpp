//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <string>
#include <boost/asio/buffer.hpp>
#include "iostream"
namespace server {

struct header
{
  std::string name;
  std::string value;
};


namespace event_strings {

	const char name_value_separator[] = { ':', ' ' };
	const char crlf[] = { '\r', '\n' };

}

struct event
{
	~event() {
		std::cout << "~event" << std::endl;
	}
	std::vector<header> m_header;
	std::string m_content;
	boost::asio::const_buffer m_buffers;

	boost::asio::const_buffer& to_buffers()
	{
		
		//for (std::size_t i = 0; i < m_header.size(); ++i)
		//{
		//	header& h = m_header[i];
		//	buffers.push_back(boost::asio::buffer(h.name));
		//	buffers.push_back(boost::asio::buffer(event_strings::name_value_separator));
		//	buffers.push_back(boost::asio::buffer(h.value));
		//	buffers.push_back(boost::asio::buffer(event_strings::crlf));
		//}
		//buffers.push_back(boost::asio::buffer(event_strings::crlf));
		m_buffers = boost::asio::buffer(m_content);
		return m_buffers;
	}

};

typedef std::shared_ptr<event> event_ptr;

} // namespace server
#endif // HTTP_HEADER_HPP
