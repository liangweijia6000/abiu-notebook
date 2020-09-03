#ifndef _config_h_
#define _config_h_

#include "../servercommon.h"

const static std::string CONFIG_PATH="./server.conf";

struct IpAddr
{
	std::string ip;
    int port;
};

struct MySQLInfo
{
    std::string ip;
    int port;
    std::string username;
    std::string password;
};

class Config
{
    SINGLETON_DECLARATION(Config)
public:
    Config();
    ~Config();
public:
    void Init();
    
    int GetIpAddr(IpAddr& info);
    void GetMySQLInfo(MySQLInfo& info);

private:
	std::map<std::string, std::map<std::string, std::string>> _configMap;

};


#endif //_config_h_