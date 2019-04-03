#include "./../client.hpp"

void Client::cmd_QUIT(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
    close(controlConnectionfd);
    exit(0);
}
