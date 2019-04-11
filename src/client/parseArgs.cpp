#include "./client.hpp"

/**parse command line arguments
 *
 * @usage
 * parse the user entered arguments
 *
 * @returns
 * a properly initialised client object
 *
*/
Client parseArgs(int argc, char** argv) {
	string IP = "127.0.0.1";
	int port = 9000;

	if (argc > 1) {
		IP = argv[1];
	}
	if (argc > 2) {
		port = atoi(argv[2]);
	}

	if (argc > 3) {
		fprintf(stdout, "\n[ERROR] Invalid Usage. \n");
		fprintf(stdout, "\nUsage :\n\t./server <ServerIP:127.0.0.1> <ServerPort:9000>");
		fprintf(stdout, "\n\t./client");
		fprintf(stdout, "\n\t./client 127.0.0.1 9000\n\n");
		exit(0);
	}

	Client ftpClient(IP, port);
	// @logging
	fprintf(stdout, "Connection to Server ...\nServer IP : %s \nPort      : %d",
			IP.c_str(), port);
	ftpClient.logClientConfiguration();

	return ftpClient;
}