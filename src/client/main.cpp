#include "./client.hpp"

Client parseArgs(int, char**);

int main(int argc, char **argv) {

    // create a FTP client
    Client ftpClient = parseArgs(argc, argv);

    // create a socket and connect to Server
    int controlConnectionfd = createSocketAndConnectToHost(
                                    ftpClient.getControlConnectionIP(), 
                                    ftpClient.getControlConnectionPortNumber()
                                );

    // log client info
    ftpClient.logClientConfiguration();

    // Start the FTP protocol
    ftpClient.initiateProtocolInterpreter(controlConnectionfd);

    return 0;
} 