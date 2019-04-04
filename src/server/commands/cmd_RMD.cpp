#include "./../server.hpp"

void Server::cmd_RMD(int controlConnectionfd, const vector<string>& args) {
    string path(args[1]);

    int stat = rmdir(path.c_str());
	if(stat!=0){
		if(errno == EEXIST || errno == ENOTEMPTY){
            Send(controlConnectionfd, "Directory not empty. Can't be deleted.");
		}
        else if(errno == ENOTDIR){
            Send(controlConnectionfd, "Not a directory. Can't be deleted.");
		}
		else{
            Send(controlConnectionfd, "Failed to delete directory.");
		}
	}
	else{
		string res = "Directory " + path + " successfully deleted.";
		Send(controlConnectionfd, res, 257);
	}
}
