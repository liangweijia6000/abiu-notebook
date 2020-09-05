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
	std::cout<<"server run"<<std::endl;

	Config::getInstance().Init();

	IpAddr info;
	Config::getInstance().GetIpAddr(info);
    printf("Load config ip:%s, port:%d", info.ip.c_str(), info.port);

    if(!NetworkManager::getInstance().Init(info))
	{
		return 0;
	}

	Service* pService = NetworkManager::getInstance().CreateService();
	if (!pService)
	{
		printf("main NetworkManager createService eroor \n");
		return 0;
	}

	if (!pService->Start())
	{
		printf("Service Start error");
		return 0;
	}	

	while (1)
	{
		usleep(10000);
		pService->Process();
	}

	return 0;
}
