//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "../share/server_manager.h"
#include "../share/logger.h"

int main(int argc, char* argv[])
{
	// name
	if (argc < 2)
	{
		assert(false);
		return -1;
	}
	
	std::cout << "main:" << boost::this_thread::get_id() << std::endl;

	if (!CServerManager::getInstance()->Init(argv[1]))
	{
		LogError("CServerManager Init Failed!");
		return -1;
	}

	if (!CServerManager::getInstance()->Start())
	{
		LogError("CServerManager Start Failed!");
		return -1;
	}

	return 0;
}
