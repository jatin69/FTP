#include "./server.hpp"

/**doesRouteToHostExist
 * This function, checks if a route to host exists.
 * 
 * @usage
 * When the server wants to `initiate` a connection,
 * it can only successfully do so, if client has a static IP,
 * that means, there should be a clear route to that HOST via internet.
 * 
 * @returns
 * true, if route exists
 * false, if route does not exist
 * 
 * @caller
 * This function is called by server from within `createDataConnection` 
 * when it wants to initiate connection. 
 * If route exists, server goes ahead and establishes the connection.
 * If route does not exist, server asks client for help in creating a data connection.
 * Then client creates the data connection, and that is then used for data transfer.
 * 
 * @code-logic
 * We try to create a socket and connect.
 * If connection is refused, then atleast path is possible, true is returned.
 * If route does not exist error pops up, false is returned.
 * 
 * Note that, because of this logic,
 * this function's code is exactly same as `createSocketAndConnectToHost`
 * with minor adjustments.
 * 
*/
bool doesRouteToHostExist(const char* host, int portNumber) {
    
    bool doesRouteExist = true;

    const char* port = to_string(portNumber).c_str();
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    struct addrinfo *res;
	int addr_status = getaddrinfo(host, port, &hints, &res);
	if (addr_status != 0){
        throw std::runtime_error("[DOES ROUTE EXIST : ERROR : getaddrinfo]");
	}

	int sock_fd;

	struct addrinfo *p;
	for (p = res; p != NULL; p = p->ai_next){
        sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	    if (sock_fd < 0){
            continue;       // try next
	    }

        int connect_status = connect(sock_fd, p->ai_addr, p->ai_addrlen);
        if (connect_status != 0){
            close(sock_fd);      // close this socket
            continue;            // try another socket
        }

        // Connect to the first one we can
        break;
	}

	// No Connection happened in the above loop
	if (p == NULL){
        if(string(strerror(errno)).compare("No route to host") == 0){
            doesRouteExist = false;
        }
	}
    freeaddrinfo(res);
    return doesRouteExist;
}