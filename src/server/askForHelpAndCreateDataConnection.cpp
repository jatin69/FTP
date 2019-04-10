#include "./server.hpp"

/**ask for help and create data connection
 * 
 * @usage
 * When the server wants to `initiate` connection and 
 * there is no route to client, it asks client for help,
 * which then creates a data connection, and that connection
 * is then used to transfer data.
 *
 * @returns
 * connection file descriptor for this new connection 
 * 
*/
int Server::askForHelpAndCreateDataConnection(int controlConnectionfd) {
    
    // create a socket and bind it to the data port
    int helperSocket = createSocketAndBindToPort(getDataConnectionPortNumber());

    // start Listening for incoming connections on this socket[HOST:PORT]
    Listen(helperSocket, 1);

    Send(controlConnectionfd, "[SERVER] Ready to receive Help");
    // @logging
    logs("[SERVER] Ready to receive Help");

    string ipAddressOfClient;
    int dataConnectionfd;
    dataConnectionfd = Accept(helperSocket, ipAddressOfClient);
    
    return dataConnectionfd;
} 