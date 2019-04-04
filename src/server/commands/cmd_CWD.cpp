#include "./../server.hpp"

void Server::cmd_CWD(int controlConnectionfd, const vector<string> &args) {
  string chdirResponse;
  int stat = chdir(args[1].c_str());
  if (stat == 0) {
    Send(controlConnectionfd, "Directory successfully changed.", 250);
  } else {
    // @todo : a lot of error handling can be done here
    Send(controlConnectionfd, "Failed to change directory.");
  }
}
