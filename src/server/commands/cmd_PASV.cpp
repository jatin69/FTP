#include "./../server.hpp"

/**PASV
 * 
 * This command tells server to "listen" on his data port rather than
 * initiate a connection when he receives a transfer service command.
 * 
 * Command not implemented yet.
*/
void Server::cmd_PASV(int controlConnectionfd) {
    Send(controlConnectionfd, "Command Not Implemented.", 502);
}
