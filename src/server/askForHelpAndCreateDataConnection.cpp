#include "./server.hpp"

int Server::askForHelpAndCreateDataConnection(int controlConnectionfd) {
    
    // start listening on data port
    
    // create a socket and bind it to the specified control port
    int helperSocket = createSocketAndBindToPort(getDataConnectionPortNumber());

    // start Listening for incoming connections on this socket[HOST:PORT]
    Listen(helperSocket, 1);

    Send(controlConnectionfd, "[SERVER] Ready to receive Help");
    logs("[SERVER] Ready to receive Help");

    string ipAddressOfClient;
    int dataConnectionfd = Accept(helperSocket, ipAddressOfClient);
            
    // int dataConnectionfd = controlConnectionfd;
    return dataConnectionfd;
} 