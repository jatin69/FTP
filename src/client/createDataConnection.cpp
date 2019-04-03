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
    Listen(dataConnectionSocketfd, 1);
    string ipAddressOfDataServer;

    // client is now ready and is listening
    // sleep(1);
    Send(controlConnectionfd, "Client Listening. Please Transfer.");

    // see if server needs any help with routing
    string serverResponse;
    Recv(controlConnectionfd, serverResponse);
    logs(serverResponse.c_str());

    int dataConnectionfd;
    if(serverResponse.find("[RESPONSE] HELP ME") == 0){   // server needs help
        logs("CLIENT HELP XXXXXXXXXXXXX");
        dataConnectionfd = provideHelpAndCreateDataConnection(controlConnectionfd);
    } 
    else{   // server is ready
        
        // accept is a blocking call. 
        // it will ensure that it only return when a connection is made.
        dataConnectionfd = Accept(dataConnectionSocketfd, ipAddressOfDataServer);
    }

    return dataConnectionfd;
}