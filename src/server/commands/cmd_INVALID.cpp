#include "./../server.hpp"

/**INVALID
 *
 * Any user entered input, that is not matched
 * with any FTP command is treated as invalid, and is sent here.
 *
*/
void Server::cmd_INVALID(int controlConnectionfd) {
	Send(controlConnectionfd, "INVALID COMMAND", 500);
}
