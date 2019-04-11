#include "./../client.hpp"

// CWD : Change working directory

void Client::cmd_CWD(int controlConnectionfd, const vector<string>& args[[gnu::unused]]) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
