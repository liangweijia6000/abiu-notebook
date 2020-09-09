#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "servercommon.h"
#include "config/config.h"
#include "network/networkmanager.h"
#include "network/service.h"

int main()
{
	printf("Server Run \n");

	Config::getInstance().Init();

	IpAddr info;
	Config::getInstance().GetIpAddr(info);
	printf("Load config ip:%s, port:%d\n", info.ip.c_str(), info.port);

	if(!NetworkManager::getInstance().Init(info))
	{
		return 0;
	}

	Service* pService = NetworkManager::getInstance().CreateService();
	if (!pService)
	{
		printf("main() NetworkManager createService eroor \n");
		return 0;
	}

	if (!pService->Start())
	{
		printf("main() service start error \n");
		return 0;
	}	

	while (1)
	{
		usleep(10000);
		pService->Process();
	}

	return 0;
}
