#include "./../client.hpp"

// CDUP : Change to parent directory

void Client::cmd_CDUP(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
