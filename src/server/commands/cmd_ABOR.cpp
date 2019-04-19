#include "./../server.hpp"

/**ABOR - Abort
 *
 * Abort the last command and any associated data transfer.
 * Usually used to kill the last data transfer (if ongoing).
 *
 * Command not implemented yet.
*/
extern pid_t parent_pid;

void Server::cmd_ABOR(int controlConnectionfd) {
	kill(-parent_pid, SIGQUIT);
	logs("DONE KILLING ON SERVER SIDE");
	kill(-parent_pid, SIGQUIT);
	Send(controlConnectionfd, "DONE KILLING ON SERVER. EDIT.", 502);
}
