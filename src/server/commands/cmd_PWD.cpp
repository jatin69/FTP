#include "./../server.hpp"

void Server::cmd_PWD(int controlConnectionfd) {
    char cwdResponse[FTP::SOCKET_READ_BUFFER_SIZE];
	getcwd(cwdResponse, sizeof(cwdResponse));
	Send(controlConnectionfd, cwdResponse, 257);
}
