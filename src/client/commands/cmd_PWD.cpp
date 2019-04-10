#include "./../client.hpp"

// PWD - display the present working directory

void Client::cmd_PWD(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
