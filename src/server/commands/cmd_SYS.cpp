#include "./../server.hpp"

void Server::cmd_SYS(int controlConnectionfd) {
    string sysType = "System Type : ";
    #ifdef WINDOWS
    sysType += "WINDOWS";
    #else
    sysType += "LINUX";
    #endif
    Send(controlConnectionfd, sysType.c_str());
}
