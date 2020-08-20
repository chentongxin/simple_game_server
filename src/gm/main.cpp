//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp> 
#include <boost/timer.hpp>
#include <boost/progress.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

void thread()
{
	try
	{
		boost::asio::io_context io_context;

		tcp::socket s(io_context);
		tcp::resolver resolver(io_context);
		boost::asio::connect(s, resolver.resolve("127.0.0.1", "10086"));
		boost::progress_timer pt;
		for (int i = 0; i < 30000; i++)
		{
			std::string request = boost::lexical_cast<std::string>(boost::this_thread::get_id()) + "---" + boost::lexical_cast<std::string>(i);
			size_t request_length = request.length();
			boost::asio::write(s, boost::asio::buffer(request.c_str(), request_length));

			char reply[max_length];
			size_t reply_length = boost::asio::read(s,
				boost::asio::buffer(reply, request_length));
		}

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}


int main(int argc, char* argv[])
{
	
	for (int i = 0; i < 10; i++)
	{
		boost::thread t1(thread);
		t1.join();
	}
	getchar();
	return 0;
}
