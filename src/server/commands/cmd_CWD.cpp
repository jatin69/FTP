#include "./../server.hpp"

// CWD : Change working directory

void Server::cmd_CWD(int controlConnectionfd, const vector<string> &args) {
  
  int stat = chdir(args[1].c_str());
  if (stat == 0) {
    Send(controlConnectionfd, "Directory successfully changed.", 250);
  } else {
    string chdirResponse("Failed to change directory.\n");
    chdirResponse.append(strerror(errno));
    Send(controlConnectionfd, chdirResponse);
  }
}
 