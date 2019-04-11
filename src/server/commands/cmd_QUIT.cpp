#include "./../server.hpp"

// QUIT - terminate connection for this client

void Server::cmd_QUIT(int controlConnectionfd) {
	Send(controlConnectionfd, "Terminating Connection", 221);
	close(controlConnectionfd);
	exit(0);
}
