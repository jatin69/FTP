#include "./../server.hpp"

void Server::cmd_SYS(int controlConnectionfd) {
    string commandToExecute = "hostnamectl | grep 'Operating System' | cut -d':' -f2";
    string sysType = "System Type : " + executeShellCommand(commandToExecute);
    Send(controlConnectionfd, sysType.c_str());
}
