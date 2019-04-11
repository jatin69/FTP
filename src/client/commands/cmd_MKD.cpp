#include "./../client.hpp"

// MKD - make directory

void Client::cmd_MKD(int controlConnectionfd, const vector<string>& args[[gnu::unused]]) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
