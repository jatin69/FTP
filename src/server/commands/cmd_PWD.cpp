#include "./../server.hpp"

void Server::cmd_PWD(int controlConnectionfd) {
    char cwd[FTP::LINE_SIZE];
	getcwd(cwd, sizeof(cwd));
	Send(controlConnectionfd, cwd, 257);
}
