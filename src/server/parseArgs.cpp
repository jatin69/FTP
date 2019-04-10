#include "./server.hpp"

/**parse command line arguments
 * 
 * @usage
 * parse the user entered arguments
 * 
 * @returns
 * a properly initialised server object
 * 
*/
Server parseArgs(int argc, char** argv){
    int port = 9000;
    int backlogs = 10;
    if(argc > 1)   { port = atoi(argv[1]);      }
    if(argc > 2)   { backlogs = atoi(argv[2]);  }

    if(argc > 3)   {
        fprintf(stdout, "\n[ERROR] Invalid Usage. \n");
        fprintf(stdout, "\nUsage :\n\t./server <port:9000> <backlogs:10>");
        fprintf(stdout, "\n\t./server");
        fprintf(stdout, "\n\t./server 9000");
        fprintf(stdout, "\n\t./server 9000 10\n\n");
        exit(0);
    }
    
    Server ftpServer(port, backlogs);
    fprintf(stdout, "Server Started at Port %d\n", port);
    
    // @logging
    ftpServer.logServerConfiguration(); 

    return ftpServer;
} 