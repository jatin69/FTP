#include "./../client.hpp"

/**HELP
 *
 * Shows information about the all possible commands.
 *
*/
void Client::cmd_HELP(const string& ftpRequest[[gnu::unused]]) {
	printf("\n ============ HELP SECTION ============ \n");

	// HELP
	printf("\nCommand   :\t%s", "Show all the available commands");
	printf("\nUsage     :\t%s\n", "HELP");

	// CLIENT Commands
	printf("\nCommand   :\t%s", "Execute a command on client");
	printf("\nUsage     :\t%s\n", "!<normal-command>");
	printf("          :\t%s\n", "!ls -la");
	printf("          :\t%s\n", "!cd ..");

	// NOOP
	printf("\nCommand   :\t%s", "No Operation");
	printf("\nUsage     :\t%s\n", "NOOP");

	// USER
	printf("\nCommand   :\t%s", "Provide username for login");
	printf("\nUsage     :\t%s\n", "USER <username>");

	// PASS
	printf("\nCommand   :\t%s", "Provide password for login");
	printf("\nUsage     :\t%s\n", "PASS <password>");

	// SYS
	printf("\nCommand   :\t%s", "Get System Details Of server");
	printf("\nUsage     :\t%s\n", "SYS");

	// PWD
	printf("\nCommand   :\t%s", "Print working directory");
	printf("\nUsage     :\t%s\n", "PWD");

	// LIST
	printf("\nCommand   :\t%s", "List directory contents");
	printf("\nUsage     :\t%s\n", "LIST <pathToDirectory>");
	printf("          :\t%s\n", "ls <pathToDirectory>");

	// CWD
	printf("\nCommand   :\t%s", "Change working directory");
	printf("\nUsage     :\t%s\n", "CWD <path>");
	printf("          :\t%s\n", "cd <path>");

	// CDUP
	printf("\nCommand   :\t%s", "Change to parent directory");
	printf("\nUsage     :\t%s\n", "CDUP");

	// MKD
	printf("\nCommand   :\t%s", "Make directory");
	printf("\nUsage     :\t%s\n", "MKD <directoryName>");
	printf("          :\t%s\n", "mkdir <directoryName>");

	// RMD
	printf("\nCommand   :\t%s", "Remove directory");
	printf("\nUsage     :\t%s\n", "RMD <directoryName>");
	printf("          :\t%s\n", "rmdir <directoryName>");

	// STOR
	printf("\nCommand   :\t%s", "Send File to Server");
	printf("\nUsage     :\t%s\n", "STOR <fileName>");
	printf("          :\t%s\n", "put <fileName>");

	// RETR
	printf("\nCommand   :\t%s", "Retrive File from Server");
	printf("\nUsage     :\t%s\n", "RETR <fileName>");
	printf("          :\t%s\n", "get <fileName>");

	// PORT
	printf("\nCommand   :\t%s", "Switch data connection IP, Port");
	printf("\nUsage     :\t%s\n", "PORT <IPAddress> <Port>");

	// QUIT
	printf("\nCommand   :\t%s", "Quit the application");
	printf("\nUsage     :\t%s\n", "QUIT");

	// ABORT
	printf("\nCommand   :\t%s", "Abort the last command and related data transfer");
	printf("\nUsage     :\t%s\n", "ABOR");

	// PASV
	printf("\nCommand   :\t%s", "Switch to Passive Receive Mode");
	printf("\nUsage     :\t%s\n", "PASV");

	// TYPE
	printf("\nCommand   :\t%s", "Switch the representation type");
	printf("\nUsage     :\t%s\n", "TYPE <A/E/I> <N/T/C>");
	printf("          :\t%s\n", "TYPE L <byte size>");

	// MODE
	printf("\nCommand   :\t%s", "Switch the transfer mode");
	printf("\nUsage     :\t%s\n", "MODE <S/B/C>");
	printf("          :\t%s\n", "Namely, Stream, Block, Compressed Mode");

	// STRU
	printf("\nCommand   :\t%s", "Switch the File structure Type  ");
	printf("\nUsage     :\t%s\n", "STRU <F/R/P>");
	printf("          :\t%s\n", "Namely, File, Record Structure, Page Structure");
	printf("\n\n");
}
