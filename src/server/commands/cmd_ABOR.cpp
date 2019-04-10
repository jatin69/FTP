#include "./../server.hpp"

/**ABOR - Abort
 * 
 * Abort the last command and any associated data transfer.
 * Usually used to kill the last data transfer (if ongoing).
 * 
 * Command not implemented yet.
*/
void Server::cmd_ABOR(int controlConnectionfd) {
    Send(controlConnectionfd, "Command Not Implemented.", 502);
}
