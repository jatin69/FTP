#include "./../server.hpp"

// RETR - get/retrive a file from server

void Server::cmd_RETR(int controlConnectionfd, const vector<string>& args) {
	int pid = fork();

	if (pid < 0) {  // error
		printError();
		throw runtime_error("[SERVER:CMD:LIST] Fork Error");
	}

	if (pid > 0) {  // parent

		// waiting for this child's completion
		int statusOfChild;
		waitpid(pid, &statusOfChild, 0);

		int exitCodeOfChild;
		if (WIFEXITED(statusOfChild)) {
			exitCodeOfChild = WEXITSTATUS(statusOfChild);
		}

		if (exitCodeOfChild == 0) {
			Send(controlConnectionfd, "Server Sent File Successfully.", 250);
			logs("Server Sent File Successfully.");
		} else {
			Send(controlConnectionfd, "Resuming Session.");
		}

		string ftpResponse;
		Recv(controlConnectionfd, ftpResponse);
		logs(ftpResponse.c_str());
	}

	if (pid == 0) {  // child

		int dataConnectionfd = createDataConnection(controlConnectionfd);

		// Child no longer needs control connection, we can close it
		close(controlConnectionfd);

		// @logging
		// logs(getDataConnectionIP());
		// logv(getDataConnectionPortNumber());

		Send(dataConnectionfd, "Sending File in Binary Mode.");

		string fileName(args[1]);
		SendFile(dataConnectionfd, fileName);
		//  @logging
		logs("File Sent.");

		/**Important Note -
		 *
		 * don't send anything else now.
		 * client knows about completion because of connection termination.
		 *
		 * if anything more is sent here, it will be assumed as part of the file
		 * and will be appended in file at the client side.
		*/

		// child will exit upon completion of its task
		close(dataConnectionfd);
		exit(0);
	}
}
