#include "./server.hpp"

void Server::cmd_NOOP(int controlfd) {
    Send(controlfd, "Command OK. No Operation.", 200);
}

void Server::cmd_INVALID(int controlfd) {
    Send(controlfd, "INVALID COMMAND", 331);
}