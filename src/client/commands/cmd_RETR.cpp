#include "./../client.hpp"

// RETR - get/retrive a file from server

void Client::cmd_RETR(int controlConnectionfd, const vector<string>& args) {
	
	string ftpResponse;

	/**Create a child - As per RFC 959
	 *
	 * Why are we creating a child?
	 * When the client requests a big stream of data, the data is to be
	 * transferred by the connectionControlfd and not the controlfd.
	 * This reponsibility of creating and destroying the connectionControlfd
	 * is given to the child process.
	 * Parent waits for child to complete. Once the child has done its work,
	 * The final response is collected by controlfd.
	*/
	int pid = fork();
	if (pid < 0) {  // error
		printError();
		throw runtime_error("[CLIENT:CMD:LIST] Fork Error");
	}
	
	if (pid > 0) {  // parent

		/**If we don't do anything here, parent starts to race for `receive control connection`
		 * Instead of child getting the transfer request,
		 * the parent gets the transfer request.
		 * 
		 * 
		 * PARENT MUST WAIT UNTIL A DATA CONNECTION IS CREATED. THEN IT CAN RETURN to accept ABORT FROM USER.
		*/

		// waiting for this child's completion
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

		Recv(controlConnectionfd, ftpResponse);
		logs(ftpResponse.c_str());
		
		if (exitCodeOfChild == 10) {
			Send(controlConnectionfd, "Resuming session");
			logs("Resuming session");
			// Send(controlConnectionfd, "Client Received File Successfully.");
			// logs("Client Received File Successfully.");
		} else {
			logs("BLAHH");
			// Send(controlConnectionfd, "Resuming session");
			// logs("Resuming session");
		}
	} 
	
	if (pid == 0) {  // child

		/**Data Connection fd
		 *
		 * The client starts passively listening to the
		 * [HOST:PORT] socket specified by [PORT Command OR Default]
		 * The server actively connects to client and transfers data.
		 *
		 * In case the PORT command is explicitly used and the dump is to be
		 * received elsewhere, we allow that IP to receive data
		*/

		// Remote DUMP Mode : allow that IP to accept data

		// @todo
		// @todo : what to do about this thing - probably move it about the data connection line.
		// the exit line will then be remove
		// if (string("CURRENT_MACHINE_IP").compare(getDataDumpReceiverIP()) != 0) {
		// 	handleDataDumpProcessAtRemoteIP();
		// 	exit(0);
		// }

		// Normal DUMP mode

		/**Special Note : Race Condition Resolving
		 *
		 * It is extremely important that we create this data connection
		 * and start listening before the server attempts to connect.
		 *
		*/ 
		// @abort
		int dataConnectionfd = createDataConnection(controlConnectionfd);

		// send a signal to parent that he is safe to return now
		int newp = fork();
		if(newp > 0){
			string s = executeShellCommand("ps fj");
			logs(s.c_str());
			logs("CHECK NOW ..");
			// sleep(4000);
			// negative exit code is not working, it has to be positive
			exit(10);
		}
		else{
			// Child no longer needs control connection, we can close it
			close(controlConnectionfd);

			// @logging
			logs(getDataDumpReceiverIP());
			logv(getDataDumpReceiverPortNumber());

			Recv(dataConnectionfd, ftpResponse);
			logs(ftpResponse.c_str());

			string fileName(args[1]);
			logs("CLient receive inititated");
			RecvFile(dataConnectionfd, fileName);
			logs("Client receiving done.");

			// child will exit upon completion of its task
			close(dataConnectionfd);
			exit(0);
		}
	}
}
