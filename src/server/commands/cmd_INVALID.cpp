#include "./../server.hpp"

void Server::cmd_INVALID(int controlConnectionfd) { 
    Send(controlConnectionfd, "INVALID COMMAND", 500); 
}
