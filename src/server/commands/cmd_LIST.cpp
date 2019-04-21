#include "./../server.hpp"

// LIST - list the directory contents

void Server::cmd_LIST(int controlConnectionfd, const vector<string>& tokens) {
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
			Send(controlConnectionfd, "Directory Listing Send OK.", 226);
		} else {
			Send(controlConnectionfd, "Resuming Session.");
		}
	}

	if (pid == 0) {  // child

		int dataConnectionfd = createDataConnection(controlConnectionfd);
		// Child no longer needs control connection, we can close it
		close(controlConnectionfd);

		// @logging
		// logs(getDataConnectionIP());
		// logv(getDataConnectionPortNumber());

		string commandToExecute = "ls -lA ";
		for (auto it = tokens.begin() + 1; it != tokens.end(); ++it) {
			commandToExecute += " " + *it;
		}
		string outputOfCommand = executeShellCommand(commandToExecute);
		Send(dataConnectionfd, "Directory Listing is as follows :");
		Send(dataConnectionfd, outputOfCommand);

		// child will exit upon completion of its task
		close(dataConnectionfd);
		exit(0);
	}
}
 