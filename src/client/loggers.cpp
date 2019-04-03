#include "./client.hpp"

void Client::logClientConfiguration() {
    logs("Client config is : ");
    logv(controlConnectionIP);
    logv(controlConnectionPortNumber);
    logv(dataDumpReceiverIP);
    logv(dataDumpReceiverPortNumber);
    
}
