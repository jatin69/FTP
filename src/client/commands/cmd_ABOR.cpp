#include "./../client.hpp"

/**ABOR - Abort
 *
 * Abort the last command and any associated data transfer.
 * Usually used to kill the last data transfer (if ongoing).
 *
 * This command has to be executed on server.
 * Only the data-connection-processes of this client should be terminated.
*/
extern pid_t parent_pid;

// @abort
void Client::cmd_ABOR(int controlConnectionfd) {
	
	logs("[CLIENT] KILL started.");
	kill(-parent_pid, SIGQUIT);
	logs("[CLIENT] KILL DONE.");
	
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
