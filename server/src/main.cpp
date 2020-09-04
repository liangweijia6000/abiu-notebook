#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <vector>

#include "servercommon.h"
#include "config/config.h"

int main()
{
	std::cout<<"server run"<<std::endl;

	Config::getInstance().Init();

	IpAddr info;
	Config::getInstance().GetIpAddr(info);
	std::cout<<info.ip<<std::endl;
	std::cout<<info.port<<std::endl;

	int socketfd = 0;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
	{
		return false;
	}

	int flags = fcntl(socketfd, F_GETFL, 0);
	fcntl(socketfd, F_SETFL, flags | O_NONBLOCK);

	struct sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(this->ip.c_str());
	sockaddr.sin_port = htons(info.port);

	int res = bind(socketfd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
	if (res < 0)
	{
		printf("Service::Start bind error\n");
		return false;
	}

	res = listen(socketfd, 512);
	if (res < 0)
	{
		printf("Service::Start listen error\n");
		return false;
	}

	struct sockaddr_in remoteAddr;

	unsigned int structLen = sizeof(struct sockaddr);

	std::vector<int> socketfdVec;

	while(true)
	{
        usleep(100000);

        //std::cout<<"connection count:"<<socketfdVec.size()<<std::endl;

		int acceptfd = accept(socketfd, (struct sockaddr *)&remoteAddr, &structLen);
		if (acceptfd == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		{
			//
		}else
		{
            char buff[INET_ADDRSTRLEN + 1] = {0};  
            inet_ntop(AF_INET, &remoteAddr.sin_addr, buff, INET_ADDRSTRLEN);  
            uint16_t port = ntohs(remoteAddr.sin_port);
            std::cout<<"on client connected :"<<buff<<":"<<port<<std::endl;
			socketfdVec.push_back(acceptfd);
		}

		for (auto it = socketfdVec.begin(); it != socketfdVec.end(); ++it)
		{
			char buf[BUFSIZ];
			memset(buf, 0, BUFSIZ);
			int len = recv(*it, buf, BUFSIZ, 0);
			if ((len < 0 && errno != EWOULDBLOCK) || len == 0)
			{
                std::cout<<"connection closed"<<std::endl;
				socketfdVec.erase(it);
				it--;
				continue;
			}

			std::cout<<"Service::Process recv:"<<buf<<std::endl;
		}
	}
}
