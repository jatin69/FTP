#include "./../client.hpp"

// USER - accepts username and asks for password

void Client::cmd_USER(int controlConnectionfd,
					  const vector<string>& args[[gnu::unused]]) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
