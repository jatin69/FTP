#include "./client.hpp"

/**provide help to server in creating a data connection
 * 
 * @working
 * Server knows it needs help. It starts listening on data port.
 * Client has server IP. It simply goes and connects to server's data port.
 * 
*/
int Client::provideHelpAndCreateDataConnection(int controlConnectionfd) {

    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    // @logging
    logs(ftpResponse.c_str());

    // connect  to server on data port
    int dataConnectionfd;
    dataConnectionfd = createSocketAndConnectToHost(
        getControlConnectionIP(), 
        getDataDumpReceiverPortNumber()
    );
    return dataConnectionfd;
}  