#include "./../server.hpp"

// PWD - display the present working directory

void Server::cmd_PWD(int controlConnectionfd) {
    char cwdResponse[FTP::SOCKET_READ_BUFFER_SIZE];
	getcwd(cwdResponse, sizeof(cwdResponse));
	Send(controlConnectionfd, cwdResponse, 257);
}
