#include "./server.hpp"

Server parseArgs(int, char**);
void handleZombieProcesses();

int main(int argc, char **argv) {

    // create a FTP server
    Server ftpServer = parseArgs(argc, argv);
    
    // create a socket and bind it to the specified control port
    int serverControlfd = createSocketAndBindToPort(ftpServer.getControlPortNumber());

    // start Listening for incoming connections on this socket[HOST:PORT]
    Listen(serverControlfd, ftpServer.getBacklogsPermitted());
    printInfo("Server Listening at ", ftpServer.getControlPortNumber());
    
    // @todo
    handleZombieProcesses();
    
    // ftpServer.initiateProtocolInterpretor();

    while(true) {
        int connectionControlfd = Accept(serverControlfd);
        if(connectionControlfd < 0){
            printError("[CONNECTION] : Couldn't accept connection");
            continue;
        }
        
        if(ftpServer.isVerbose()){
            printInfo("New Connection Accepted. Creating Process to handle this.");
        }

        // create a new process to handle this connection
        int pid = fork();

        if(pid == -1){
            printError("[FORK] : Couldn't create a new process.");
            continue;
        }

        if(pid == 0){    // Child process
    
            /**Child does not need server control
             * It's only job is to server the current connection
            */
            close(serverControlfd);

            // Start the Server-PI for this connection
            ftpServer.initiateProtocolInterpreter(connectionControlfd);

            // close the connection once work is done
            close(connectionControlfd);

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
            close(connectionControlfd);
        }
        
    } // end:while

    return 0;

} // end:main
