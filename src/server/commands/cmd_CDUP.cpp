#include "./../server.hpp"

// CDUP : Change to parent directory

void Server::cmd_CDUP(int controlConnectionfd) {
    string chdirResponse;
    string pathToChange = "..";
    int stat = chdir(pathToChange.c_str());
    if (stat == 0) {
        Send(controlConnectionfd, "Directory successfully changed.", 250);
    } else {
        string chdirResponse("Failed to change directory.\n");
        chdirResponse.append(strerror(errno));
        Send(controlConnectionfd, chdirResponse);
    }
}
 