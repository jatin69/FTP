#include "./../server.hpp"

void Server::cmd_MKD(int controlConnectionfd, const vector<string>& args) {
    string path(args[1]);

    int stat = mkdir(path.c_str(), 0775);
	if( stat!=0){
		if(errno == EEXIST){
            Send(controlConnectionfd, "Directory already exists.");
		}else{
            Send(controlConnectionfd, "Failed to create directory.");
		}
	}
    else{
        string res = "Directory " + path + " successfully created.";
        Send(controlConnectionfd, res);
	}
}
