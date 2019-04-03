#include "./server.hpp"

// @todo
// Parse properly. Handle all cases.
// Display Usage and exit in case of incomplete args
// also Show what will be used once initialisation is done

Server parseArgs(int argc, char** argv){
    int port = 9000;
    int backlogs = 10;
    if(argc > 1)   { port = atoi(argv[1]);      }
    if(argc > 2)   { backlogs = atoi(argv[2]);  }
    
    Server ftpServer(port, backlogs);
    fprintf(stdout, "Server Started at Port %d\n", port);
    ftpServer.logServerConfiguration(); 
    return ftpServer;
}