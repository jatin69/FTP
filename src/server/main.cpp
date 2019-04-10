#include "./server.hpp"
 
// prototypes for functions used below

// parsing user's command line arguments
Server parseArgs(int, char**);

// reaper of zombies
void handleZombieProcesses();

// signal handlers
void segmentationFaultHandler(int sig); 

/**Hashed User pass table
 * 
 * Server has a set of credentials.
 * Only user who verify these credentials are allowed access to server.
 * To add a user, simply put his userId, password here
 * 
 * Now these can't be store in plaintext because of security reasons.
 * so we store them as a one-way-hash values (md5, etc)
 * 
 * For now, we keep it as plaintext for easy accessibility.
*/
vector<pair<string, string>> hashedUserPassTable = {
    { "id", "pass" }, { "root", "root" }, { "jatin", "root" }
};

// execution of server executable starts from here
int main(int argc, char **argv) {

    // installing segmentation fault handler
    signal(SIGSEGV, segmentationFaultHandler); 
    
    // create a FTP server by parsing user arguments
    Server ftpServer = parseArgs(argc, argv);
    
    // create a socket and bind it to the specified control port
    int serverControlfd = createSocketAndBindToPort(ftpServer.getControlConnectionPortNumber());

    // start Listening for incoming connections on this socket[HOST:PORT]
    Listen(serverControlfd, ftpServer.getBacklogsPermitted());
    printInfo("Server Listening at ", ftpServer.getControlConnectionPortNumber());
    
    // @todo : run periodically?
    // handles zombie processes
    handleZombieProcesses();
    
    while(true) { 

        // start accepting connections
        string ipAddressOfClient;
        int controlConnectionfd = Accept(serverControlfd, ipAddressOfClient);
        if(controlConnectionfd < 0){
            printError("[CONNECTION] : Couldn't accept connection");
            continue;
        }
        

        string connectionInfo = string("[SERVER] Got connection from ") + ipAddressOfClient;
        printInfo(connectionInfo.c_str());
        
        // create a new process to handle this connection
        printInfo("New Connection Accepted. Creating Process to handle this.");
        int pid = fork();

        if(pid == -1){    // error
            printError("[FORK] : Couldn't create a new process.");
            continue;
        }

        if(pid == 0){    // Child process
    
            /**Child does not need server control
             * It's only job is to server the current connection
            */
            close(serverControlfd);

            // set client IP in this instance of server object
            ftpServer.setControlConnectionIP(ipAddressOfClient.c_str());
            // @logging
            ftpServer.logServerConfiguration();
            
            // Start the Server-PI for this connection
            ftpServer.initiateProtocolInterpreter(controlConnectionfd);

            // close the connection once work is done
            close(controlConnectionfd);

            /**Child has served its purpose, it can exit now
             * 
             * Note that the parent doesn't collect the child's exit status
             * and keeps on doing his work. Therefore, 
             * the child becomes a Zombie process. 
             * These Zombie processes need to be reaped off manually.
            */
            exit(0);
        }
        else{           // parent process

            /**Parent no longer needs the connection control
             * It has passed on the control to its child.
            */
            close(controlConnectionfd);
        }
        
    } // end:while

    return 0;

} // end:main

/**Segmentation Fault Handler
 * 
 * Whenever the SIGSEGV signal is raised, 
 * it is redirected here.
 * 
 * This informs us in detail, when a client connection dies abruptly.
 * 
*/
void segmentationFaultHandler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}