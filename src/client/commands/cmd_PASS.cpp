#include "./../client.hpp"

// PASS - accepts password and authenticates the USER

int Client::cmd_PASS(int controlConnectionfd, const vector<string>& args[[gnu::unused]]) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
	if (ftpResponse.find("[RESPONSE] [AUTHENTICATION:FAILURE] Retry") == 0) {
		return 0;
	} else {
		return 1;
	}
}
