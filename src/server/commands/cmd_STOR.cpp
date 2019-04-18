#include "./../server.hpp"

// STOR - put/store a file on server

void Server::cmd_STOR(int controlConnectionfd, const vector<string>& args) {
	string ftpResponse;
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

		Recv(controlConnectionfd, ftpResponse);
		// @logging
		logs(ftpResponse.c_str());

		if (exitCodeOfChild == 0) {
			Send(controlConnectionfd, "Server Received File Successfully.", 250);
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

		Recv(dataConnectionfd, ftpResponse);
		logs(ftpResponse.c_str());

		Send(dataConnectionfd, "Server Ready To Receive file.");
		logs("Server Ready To Receive file.");

		string fileName(args[1]);
		RecvFile(dataConnectionfd, fileName);
		logs("File Received.");

		// child will exit upon completion of its task
		close(dataConnectionfd);
		exit(0);
	}
}
