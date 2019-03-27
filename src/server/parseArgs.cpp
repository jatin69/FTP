#include "./server.hpp"

// @todo
// Parse properly. Handle all cases.
// Display Usage and exit in case of incomplete args
// also Show what will be used once initialisation is done

Server parseArgs(int argc, char** argv){
    Server ftpServer(9000, 9001, true);
    if(ftpServer.isVerbose()){
        // print a lot of details
        fprintf(stdout, "Using Defaults. ./server 9000 9001 -v");
        ftpServer.logServerConfiguration();
    }
    return ftpServer;
}