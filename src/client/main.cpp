#include "./client.hpp"

// prototypes for functions used below

// parsing user's command line arguments
Client parseArgs(int, char**);

// signal handlers
void segmentationFaultHandler(int sig);

// execution of client executable starts from here
int main(int argc, char** argv) {
	// segmentation fault handler
	signal(SIGSEGV, segmentationFaultHandler);

	// create a FTP client
	Client ftpClient = parseArgs(argc, argv);

	// create a socket and connect to Server
	int controlConnectionfd = createSocketAndConnectToHost(
		ftpClient.getControlConnectionIP(), ftpClient.getControlConnectionPortNumber());

	// Start the FTP protocol
	ftpClient.initiateProtocolInterpreter(controlConnectionfd);
	return 0;
}

/**Segmentation Fault Handler
 *
 * Whenever the SIGSEGV signal is raised,
 * it is redirected here.
 *
*/
void segmentationFaultHandler(int sig) {
	void* array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}