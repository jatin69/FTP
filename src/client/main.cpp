#include "./client.hpp"

Client parseArgs(int, char**);

int main(int argc, char **argv) {

    // create a FTP client
    Client ftpClient = parseArgs(argc, argv);

    // create a socket and connect to Server
    int clientControlfd = createSocketAndConnectToHost(ftpClient.getServerIP(), ftpClient.getServerPortNumber());

    // Start the FTP protocol
    ftpClient.initiateProtocolInterpreter(clientControlfd);

    return 0;
} 