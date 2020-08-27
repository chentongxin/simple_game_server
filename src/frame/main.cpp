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
