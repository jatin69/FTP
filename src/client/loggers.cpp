#include "./client.hpp"

void Client::logClientConfiguration() {
    if(isVerbose()){
        logs("Client config is : ");
        logv(controlConnectionIP);
        logv(controlConnectionPortNumber);
        logv(dataDumpReceiverIP);
        logv(dataDumpReceiverPortNumber);
        logv(isVerboseModeOn);
    }
}
