#include "./server.hpp"

void Server::logServerConfiguration() {
    if(isVerbose()){
        logs("Server config is : ");
        logv(controlPortNumber);
        logv(dataConnectionPortNumber);
        logv(isVerboseModeOn);
        logv(backlogsPermitted);
        logv(extraBuffer);
    }
}
