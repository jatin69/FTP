#include "./../client.hpp"

// SYS - tells the type of system

void Client::cmd_SYS(int controlConnectionfd) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
