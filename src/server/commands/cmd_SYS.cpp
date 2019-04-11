#include "./../server.hpp"

// SYS - tells the type of system

void Server::cmd_SYS(int controlConnectionfd) {
	string commandToExecute = "hostnamectl | grep 'Operating System' | cut -d':' -f2";
	string sysType = "System Type : " + executeShellCommand(commandToExecute);
	Send(controlConnectionfd, sysType, 211);
}
