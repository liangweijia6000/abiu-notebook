#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "../servercommon.h"

struct IpAddr;

class Service
{
private:
    /* data */
public:
    Service(IpAddr ipAddr);
    ~Service();
public:
    bool Start();
    void Stop();
    void Reset(IpAddr ipAddr);
    void Process();
    void SendMsg(char* msg);
    bool IsRun();
private:
private:
    std::string ip;
    int port;
    int socketfd;
    std::vector<int> socketfdVec;
    bool isRun;
};

#endif  //_SERVICE_H_
