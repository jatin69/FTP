#include "./../server.hpp"

void Server::cmd_NOOP(int controlConnectionfd) {
    Send(controlConnectionfd, "Command OK. No Operation.", 200);
}
