#include <sys/socket.h>
#include "networkmanager.h"
#include "../config/config.h"

SINGLETON_DEFINITION(NetworkManager)

NetworkManager::NetworkManager()
{
    //
}

NetworkManager::~NetworkManager()
{
    //
}

bool NetworkManager::Init(IpAddr ipAddr)
{
    this->ipAddr = ipAddr;
    return true;
}

Service* NetworkManager::CreateService()
{
    printf("NetworkManager::CreateService\n");
    if (this->pService != NULL)
    {
        this->pService = new Service(this->ipAddr);
    }else
    {
        this->pService->Reset(this->ipAddr);
    }   
    
    return this->pService;
}

Service* NetworkManager::GetService()
{
    return this->pService;
}



