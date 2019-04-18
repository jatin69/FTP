#include "./client.hpp"

// parsing user's command line arguments
Client parseArgs(int, char**);

// install Required signal handlers
void InstallSignalHandlers();

// execution of client executable starts from here
int main(int argc, char** argv) {
	try {
		// installing signal Handlers
		// Here - segmentation fault
		InstallSignalHandlers();

		// create a FTP client
		Client ftpClient = parseArgs(argc, argv);

		// create a socket and connect to Server
		int controlConnectionfd =
			createSocketAndConnectToHost(ftpClient.getControlConnectionIP(),
										 ftpClient.getControlConnectionPortNumber());

		// Start the FTP protocol
		ftpClient.initiateProtocolInterpreter(controlConnectionfd);
	} catch (const std::exception& e) {
		// catch anything thrown within try block that derives from std::exception
		std::cerr << "\n[THROWN] : " << e.what() << "\n" << endl;
	}
	return 0;
}