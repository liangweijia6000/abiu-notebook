#include "config.h"

SINGLETON_DEFINITION(Config)

Config::Config()
{
    //
}

Config::~Config()
{
    //
}


void Config::Init()
{
	std::cout<<"Load Config"<<std::endl;

    std::ifstream fileStream(CONFIG_PATH.c_str());

	std::string readStr;

	std::map<std::string, std::string>* pNodeMap;

	while (getline(fileStream, readStr))
	{
		std::string::size_type pos1 = readStr.find('[');
		std::string::size_type pos2 = readStr.find(']');

		if (std::string::npos == pos1 || std::string::npos == pos2)
		{
			if(!pNodeMap)
			{
				continue;
			}

			std::string::size_type pos = readStr.find('=');
			if(pos == std::string::npos)
			{
				continue;
			}

			std::string keyStr = readStr.substr(0, pos);
			std::string valueStr = readStr.substr(pos + 1, readStr.size()-1);

			(*pNodeMap)[keyStr] = valueStr;

			continue;
		}

		std::string strSection = readStr.substr(pos1=1, pos2-1);

		if(_configMap.find(strSection) == _configMap.end())
		{
			std::map<std::string, std::string> nodeMap;
			_configMap[strSection] = nodeMap;
		}

		pNodeMap = &_configMap[strSection];
	}
}

void Config::GetIpAddr(IpAddr& info)
{
	//
}

void Config::GetMySQLInfo(MySQLInfo& info)
{
	//
}