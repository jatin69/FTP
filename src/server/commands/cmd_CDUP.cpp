#include "./../server.hpp"

void Server::cmd_CDUP(int controlConnectionfd) {
  string chdirResponse;
  string pathToChange = "..";
  int stat = chdir(pathToChange.c_str());
  if (stat == 0) {
    Send(controlConnectionfd, "Directory successfully changed.", 250);
  } else {
    // @todo : a lot of error handling can be done here
    Send(controlConnectionfd, "Failed to change directory.");
  }
}
