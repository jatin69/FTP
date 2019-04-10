#include "./client.hpp"

/**client config logger
 * Logs client's current configuration.
*/
void Client::logClientConfiguration() {
    logs("Client config is : ");
    logv(controlConnectionIP);
    logv(controlConnectionPortNumber);
    logv(dataDumpReceiverIP);
    logv(dataDumpReceiverPortNumber);
    
}
