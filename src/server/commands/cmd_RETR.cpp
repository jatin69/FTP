#include "./../server.hpp"

// RETR - get/retrive a file from server
void Server::cmd_RETR(int controlConnectionfd, const vector<string>& args) {
	int pid = fork();
	if (pid < 0) {  // error
		printError();
		throw runtime_error("[SERVER:CMD:LIST] Fork Error");
	}
 
	if (pid > 0) {  // parent

		/**If we don't do anything here, parent starts to race for `receive control connection`
		 * Instead of child getting the transfer request,
		 * the parent gets the transfer request.
		 * 
		 * 
		 * PARENT MUST WAIT UNTIL A DATA CONNECTION IS CREATED. 
		 * THEN IT CAN RETURN to accept ABORT FROM USER.
		*/

		int statusOfChild ;
		if(waitpid(pid, &statusOfChild, 0)==-1){
			printError();
		}
		int exitCodeOfChild;
		if (WIFEXITED(statusOfChild)) {
			exitCodeOfChild = WEXITSTATUS(statusOfChild);
		}
		logs("I FOUND EXIT CODE.");
		logv(exitCodeOfChild);

		if (exitCodeOfChild == 10) {
			Send(controlConnectionfd, "Resuming Session.");
			logs("Resuming session.");
			// Send(controlConnectionfd, "Server Sent File Successfully.", 250);
			// logs("Server Sent File Successfully.");
		} else {
			logs("BLAH");
			// Send(controlConnectionfd, "Resuming Session.");
		}

		string ftpResponse;
		Recv(controlConnectionfd, ftpResponse);
		logs(ftpResponse.c_str());
	}

	if (pid == 0) {  // child

		// @abort
		int dataConnectionfd = createDataConnection(controlConnectionfd);

		// send a signal to parent that he is safe to return now
		int newpid = fork();
		if(newpid > 0){
			// changing the process's group id to its parent
			// so its grandfather can wait for him
			// int ppid = getppid();
			// setpgid(0, myid);
			logs("CHECK NOW ..");
			string s = executeShellCommand("ps fj");
			logs(s.c_str());

			exit(10);
		}
		else{
	
			// Child no longer needs control connection, we can close it
			close(controlConnectionfd);

			// @logging
			// logs(getDataConnectionIP());
			// logv(getDataConnectionPortNumber());

			Send(dataConnectionfd, "Sending File in Binary Mode.");

			string fileName(args[1]);
			logs("Server Send inititated");
			SendFile(dataConnectionfd, fileName);
			logs("Server Sent file");

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
}
