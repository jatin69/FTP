#include "./server.hpp"

/**server config logger
 * Logs server's current configuration.
*/
void Server::logServerConfiguration() {
	logs("Server config is : ");
	logv(controlConnectionIP);
	logv(controlConnectionPortNumber);
	logv(dataConnectionIP);
	logv(dataConnectionPortNumber);
	logv(backlogsPermitted);
}
