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

/**print Info
 *
 * print user's custom message
*/
void Client::printInfo(const char* msg) {
	fprintf(stdout, "\n[INFO] : %s\n", msg);
}

/**print Info : overloaded
 *
 * print user's custom message with a value
*/
void Client::printInfo(const char* msg, int value) {
	printInfo((string(msg) + to_string(value)).c_str());
}