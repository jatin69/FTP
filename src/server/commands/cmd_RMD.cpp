#include "./../server.hpp"

// RMD - remove directory

void Server::cmd_RMD(int controlConnectionfd, const vector<string> &args) {
	string path(args[1]);
	int stat = rmdir(path.c_str());
	if (stat != 0) {
		string chdirResponse("Failed to delete directory.\n");
		chdirResponse.append(strerror(errno));
		Send(controlConnectionfd, chdirResponse);
	} else {
		string res = "Directory " + path + " successfully deleted.";
		Send(controlConnectionfd, res, 257);
	}
}
 