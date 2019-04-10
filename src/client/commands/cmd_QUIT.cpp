#include "./../client.hpp"

// QUIT - terminate connection with server

void Client::cmd_QUIT(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
    close(controlConnectionfd);
    exit(0);
}
