#include "./../client.hpp"

// RMD - remove directory

void Client::cmd_RMD(int controlConnectionfd, const vector<string>& args[[gnu::unused]]) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
