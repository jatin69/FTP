#include "./client.hpp"

// parsing user's command line arguments
Client parseArgs(int, char**);

// install Required signal handlers
void InstallSignalHandlers();

pid_t parent_pid;

// execution of client executable starts from here
int main(int argc, char** argv) {


/**Wrapper : Installing signal handlers
 * 
 * Hides away the complexity of signal installation. 
 * To add a new signal handler, do it inside this function.
 * 
 * @currently-used-handlers
 * 1. reaper of zombie processes
 * 
*/
InstallSignalHandlers();

	parent_pid = getpid();

	if(fork()==0){
		if(fork()==0){
			while(true);	
		}
		if(fork()==0){
			while(true);	
		}
		while(true);
	}
	else{
		sleep(5);
		cout << "ALIVE\n";
		kill(-parent_pid, SIGQUIT);
	}
	cout << "WIRD\n";	
	sleep(5);
	// exit(0);
 
	try {
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