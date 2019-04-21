#include "./../client.hpp"

// USER - accepts username and asks for password

void Client::cmd_USER(int controlConnectionfd, const vector<string>& args) {
	
	string ftpUser(args[1]);
	setClientUsername(ftpUser);

	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
