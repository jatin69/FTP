#include "./server.hpp"

void Server::logServerConfiguration() {
    logs("Server config is : ");
    logv(controlConnectionIP);
    logv(controlConnectionPortNumber);
    logv(dataConnectionIP);
    logv(dataConnectionPortNumber);    
    logv(backlogsPermitted);
}
