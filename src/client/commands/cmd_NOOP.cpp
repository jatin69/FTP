#include "./../client.hpp"

// NOOP : No operation

void Client::cmd_NOOP(int controlConnectionfd) { 
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
