#include "./../server.hpp"

// USER - accepts username and asks for password

void Server::cmd_USER(int controlConnectionfd, const vector<string>& args) {
	bool isUsernameOK = false;
	string ftpUser(args[1]);

	for (auto it : hashedUserPassTable) {
		if (oneWayHash(ftpUser) == it.first) {
			isUsernameOK = true;
			break;
		}
	}
	if (isUsernameOK) {
		Send(controlConnectionfd, "Username OK. Needs Password", 331);
		setClientUsername(ftpUser);
	} else {
		Send(controlConnectionfd, "User Not found. Make sure the user exists.", 332);
	}
}
 