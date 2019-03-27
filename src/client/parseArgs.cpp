#include "./client.hpp"

// @todo
// Parse properly. Handle all cases.
// Display Usage and exit in case of incomplete args
// also Show what will be used once initialisation is done

Client parseArgs(int argc, char** argv){
    Client ftpClient("127.0.0.1", 9000, true);
    if(ftpClient.isVerbose()){
        // print a lot of details
        fprintf(stdout, "Using Defaults. ./client 127.0.0.1 9000 -v");
    }
    return ftpClient;
}