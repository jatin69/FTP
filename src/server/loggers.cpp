#include "./server.hpp"

void Server::logServerConfiguration() {
    if(isVerbose()){
        logs("Server config is : ");
        logv(controlConnectionIP);
        logv(controlConnectionPortNumber);
        logv(dataConnectionIP);
        logv(dataConnectionPortNumber);
        logv(isVerboseModeOn);
        logv(backlogsPermitted);
    }
}
