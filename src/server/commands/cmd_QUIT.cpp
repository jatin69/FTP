#include "./../server.hpp"

void Server::cmd_QUIT(int controlConnectionfd) {
    Send(controlConnectionfd, "Terminating Connection", 221);
    close(controlConnectionfd);
    exit(0);
}
