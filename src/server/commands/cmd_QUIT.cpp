#include "./../server.hpp"

void Server::cmd_QUIT(int controlConnectionfd) {
    Send(controlConnectionfd, "Terminating Connection", 200);
    close(controlConnectionfd);
    exit(0);
}
