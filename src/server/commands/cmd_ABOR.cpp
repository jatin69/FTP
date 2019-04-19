#include "./../server.hpp"

/**ABOR - Abort
 *
 * Abort the last command and any associated data transfer.
 * Usually used to kill the last data transfer (if ongoing).
 *
 * Command not implemented yet.
*/
extern pid_t parent_pid;

// @abort
void Server::cmd_ABOR(int controlConnectionfd) {
	logs("[SERVER] KILL started.");
	kill(-parent_pid, SIGQUIT);
	logs("[SERVER] KILL DONE.");
	Send(controlConnectionfd, "[SERVER] KILL DONE.", 502);
}
