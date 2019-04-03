#include "./../client.hpp"

void Client::cmd_CDUP(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
