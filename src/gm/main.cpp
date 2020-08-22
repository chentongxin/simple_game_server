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
#include <boost\timer.hpp>
#include <boost\progress.hpp>
#include <boost/atomic/atomic.hpp>

using boost::asio::ip::tcp;
using std::string;

enum { max_length = 1024 };

boost::atomic_int count = 0;

int post(const string& host, const string& port, const string& page, const string& data, string& reponse_data)
{
	try
	{
		boost::progress_timer pt;
		boost::asio::io_service io_service;
		//如果io_service存在复用的情况
		if (io_service.stopped())
			io_service.reset();

		// 从dns取得域名下的所有ip
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(host, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// 尝试连接到其中的某个ip直到成功 
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "POST " << page << " HTTP/1.0\r\n";
		request_stream << "Host: " << host << ":" << port << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Content-Length: " << data.length() << "\r\n";
		request_stream << "Content-Type: application/x-www-form-urlencoded\r\n";
		request_stream << "Connection: close\r\n\r\n";
		request_stream << data;

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		//将boost::asio::streambuf转为std::string
		boost::asio::streambuf::const_buffers_type cbt = response.data();
		std::string response_data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));

		count++;
		std::cout << count << std::endl;
	}
	catch (std::exception& e)
	{
		reponse_data = e.what();
		std::cout << "异常:" << e.what() << std::endl;
		return -4;
	}
	return 0;
}

void thread()
{
	try
	{
		/*	boost::asio::io_context io_context;

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
			}*/
		string host = "127.0.0.1";
		string port = "10080";
		string page = "/auth/login";
		string data = "{\"name\":12345}";
		string reponse_data;
		for (int i = 0; i < 1; i++)
		{
			int ret = post(host, port, page, data, reponse_data);
			if (ret != 0)
				std::cout << "error_code:" << ret << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}


int main(int argc, char* argv[])
{
	{
		for (int i = 0; i < 20000; i++)
		{
			boost::thread t1(thread);
			t1.join();
		}
	}
	std::cout << "返回：" << count << std::endl;
	getchar();
	return 0;
}
