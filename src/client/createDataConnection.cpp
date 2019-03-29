#include "./client.hpp"

int Client::createDataConnection(int controlConnectionfd) {

    logs("[CLIENT] : I am creating a new data Connection");
    // create socket and bind to data connection port (that we sent to server)

    /**
     * When PORT command is not explicitly used.
     * Default values are to be used.
     * 
    */
    logv(getDataDumpReceiverPortNumber());
    int dataConnectionSocketfd = createSocketAndBindToPort(getDataDumpReceiverPortNumber());
    
    // we want to accept only 1 connection, i.e. of server
    // only one connection is allowed to queue up
    Listen(dataConnectionSocketfd, 0);
    string ipAddressOfDataServer;

    // client is now ready and is listening
    // sleep(1);
    Send(controlConnectionfd, "Client Listening. Please Transfer.");

    // accept is a blocking call. 
    // it will ensure that it only return when a connection is made.
    int dataConnectionfd = Accept(dataConnectionSocketfd, ipAddressOfDataServer);

    return dataConnectionfd;

    // server actually can't connect himself
    // he needs a transfer request
    // maybe it'll be needed with NAT
}