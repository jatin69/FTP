#include "./../client.hpp"

void Client::cmd_SYS(int controlConnectionfd) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
