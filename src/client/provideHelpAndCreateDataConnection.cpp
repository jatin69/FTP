#include "./client.hpp"

int Client::provideHelpAndCreateDataConnection(int controlConnectionfd) {

    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());

    // connect  to server on data port
    int dataConnectionfd = createSocketAndConnectToHost(getControlConnectionIP(), getDataDumpReceiverPortNumber());
    // int dataConnectionfd = controlConnectionfd;
    return dataConnectionfd;
}  