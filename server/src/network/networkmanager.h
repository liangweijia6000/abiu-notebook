#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include "../servercommon.h"
#include "service.h"
#include "../config/config.h"

struct IpAddr;

class NetworkManager
{
    SINGLETON_DECLARATION(NetworkManager)
public:
	NetworkManager();
	~NetworkManager();
public:
	bool Init(IpAddr ipAddr);
	Service* CreateService();
	Service* GetService();
private:
	IpAddr ipAddr;
	Service* pService;

};


#endif  //_NETWORK_H_
