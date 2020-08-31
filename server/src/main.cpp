#include "servercommon.h"
#include "config/config.h"

int main()
{
    std::cout<<"server run"<<std::endl;

    Config::getInstance().Init();
}