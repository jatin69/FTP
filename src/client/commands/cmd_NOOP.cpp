#include "./../client.hpp"

void Client::cmd_NOOP(int controlConnectionfd) { 
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    log(ftpResponse.c_str());
}
