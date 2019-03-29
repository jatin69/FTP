#include "./../client.hpp"

void Client::cmd_PWD(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
