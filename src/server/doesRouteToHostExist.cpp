#include "./server.hpp"

// exactly same as createSocketAndConnectToHost
// just removed print statements

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
            char s[INET6_ADDRSTRLEN];
            inet_ntop(p->ai_family, _get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
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