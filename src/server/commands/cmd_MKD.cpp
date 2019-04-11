#include "./../server.hpp"

// MKD - make directory

void Server::cmd_MKD(int controlConnectionfd, const vector<string>& args) {
	string path(args[1]);

	int stat = mkdir(path.c_str(), 0775);
	if (stat != 0) {
		string chdirResponse("Failed to create directory.\n");
		chdirResponse.append(strerror(errno));
		Send(controlConnectionfd, chdirResponse);
	} else {
		string res = "Directory " + path + " successfully created.";
		Send(controlConnectionfd, res, 257);
	}
}
