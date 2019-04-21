#include "./server.hpp"

// parsing user's command line arguments
Server parseArgs(int, char**);

// install Required signal handlers
void InstallSignalHandlers();

/**Hashed User pass table
 *
 * Server has a set of credentials.
 * Only user who verify these credentials are allowed access to server.
 * To add a user, simply put his userId, password here
 *
 * Now these can't be store in plaintext because of security reasons.
 * so we store them as a one-way-hash values (md5, etc)
 *
 * For now, we keep it as plaintext for easy accessibility.
*/
vector<pair<string, string>> hashedUserPassTable = {
	{"id", "pass"}, {"root", "root"}, {"jatin", "jatin"},
};

// execution of server executable starts from here
int main(int argc, char** argv) {
	try {
		// installing signal Handlers
		// Here - segmentation fault, and zombie processes
		InstallSignalHandlers();

		// create a FTP server by parsing user arguments
		Server ftpServer = parseArgs(argc, argv);

		// create a socket and bind it to the specified control port
		int serverControlfd =
			createSocketAndBindToPort(ftpServer.getControlConnectionPortNumber());

		// start Listening for incoming connections on this socket[HOST:PORT]
		Listen(serverControlfd, ftpServer.getBacklogsPermitted());
		fprintf(stdout, "\n[INFO] Server Listening at %d\n",
				ftpServer.getControlConnectionPortNumber());

		while (true) {
			// start accepting connections
			string ipAddressOfClient;
			int controlConnectionfd = Accept(serverControlfd, ipAddressOfClient);
			if (controlConnectionfd < 0) {
				printError("[CONNECTION] : Couldn't accept connection");
				continue;
			}

			string connectionInfo =
				string("[SERVER] Got connection from ") + ipAddressOfClient;
			fprintf(stdout, "\n[INFO] %s\n", connectionInfo.c_str());

			// create a new process to handle this connection
			fprintf(stdout,
					"\nNew Connection Accepted. Creating Process to handle this.\n");
			int pid = fork();

			if (pid == -1) {  // error
				printError("[FORK] : Couldn't create a new process.");
				continue;
			}

			if (pid == 0) {  // Child process

				/**Child does not need server control
				 * It's only job is to server the current connection
				*/
				close(serverControlfd);

				// set client IP in this instance of server object
				ftpServer.setControlConnectionIP(ipAddressOfClient.c_str());
				// @logging
				ftpServer.logServerConfiguration();

				try {
					// Start the Server-PI for this connection
					ftpServer.initiateProtocolInterpreter(controlConnectionfd);

				} catch (const std::exception& e) {
					// catch anything thrown within try block that derives from
					// std::exception
					std::cerr << "\n[THROWN] : " << e.what() << "\n" << endl;
				}


				// close the connection once work is done
				close(controlConnectionfd);

				/**Child has served its purpose, it can exit now
				 *
				 * Note that the parent doesn't collect the child's exit status
				 * and keeps on doing his work. Therefore,
				 * the child becomes a Zombie process.
				 * These Zombie processes need to be reaped off manually.
				*/
				exit(0);
			} else {  // parent process

				/**Parent no longer needs the connection control
				 * It has passed on the control to its child.
				*/
				close(controlConnectionfd);
			}

		}  // end:while

	} catch (const std::exception& e) {
		// catch anything thrown within try block that derives from std::exception
		std::cerr << "\n[THROWN] : " << e.what() << "\n" << endl;
	}
	return 0;

}  // end:main
