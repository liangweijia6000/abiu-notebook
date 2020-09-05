
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "service.h"
#include "networkmanager.h"

Service::Service(IpAddr ipAddr)
{
    this->ip = ipAddr.ip;
    this->port = ipAddr.port;
    this->socketfd = -1;
    this->isRun = false;
}

Service::~Service()
{
}

void Service::Reset(IpAddr ipAddr)
{
    this->ip = ipAddr.ip;
    this->port = ipAddr.port;
    this->socketfd = -1;
}

bool Service::Start()
{
    printf("Service::Start at ip:%s port:%d\n", this->ip.c_str(), this->port);

    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd < 0)
    {
        return false;
    }

    int flags = fcntl(this->socketfd, F_GETFL, 0);
    fcntl(this->socketfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(this->ip.c_str());
    sockaddr.sin_port = htons(this->port);

    int res = bind(this->socketfd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
    if (res < 0)
    {
        printf("Service::Start bind error\n");
        return false;
    }

    res = listen(this->socketfd, 512);
    if (res < 0)
    {
        printf("Service::Start listen error\n");
        return false;
    }

    this->isRun = true;
    
    return true;
}

void Service::Stop()
{
    close(this->socketfd);
    for(auto it:this->socketfdVec)
    {
        close(it);
    }

    this->isRun =false;
}

void Service::Process()
{
    struct sockaddr_in remoteAddr;

    unsigned int structLen = sizeof(struct sockaddr);

    int acceptfd = accept(this->socketfd, (struct sockaddr *)&remoteAddr, &structLen);
    if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
    {
        //        
    }else
    {
        char buff[INET_ADDRSTRLEN + 1] = {0};
        inet_ntop(AF_INET, &remoteAddr.sin_addr, buff, INET_ADDRSTRLEN);
        uint16_t port = ntohs(remoteAddr.sin_port);
        printf("on client connected:%s, port:%d\n", buff, port);
        this->socketfdVec.push_back(acceptfd);
    }

    for (auto it = this->socketfdVec.begin(); it != this->socketfdVec.end(); ++it)
    {
        char buf[BUFSIZ];
        memset(buf, 0, BUFSIZ);
        int len = recv(*it, buf, BUFSIZ, 0);
        if ((len < 0 && errno != EWOULDBLOCK) || len == 0)
        {
            printf("connnection closed fd:%d\n", *it);
            this->socketfdVec.erase(it);
            it--;
            continue;
        }

        printf("Service::Process recv:%s\n", buf);
    }
}

void Service::SendMsg(char* msg)
{
    if (!IsRun())
    {
        return;
    }
    
    //send(this->socketfd, msg, sizeof(*msg), 0);
}

bool Service::IsRun()
{
    return this->isRun;
}

