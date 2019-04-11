#include "./client.hpp"

/**create Data Connection
 *
 * @usage
 * This function is responsible to create a data connection and
 * return the data-connection-file-descriptor
 *
 * @args-justification
 * This function in itself does not need any arguments,
 * and yet controlConnectionfd is passed.
 *
 * This is because,
 * server has to receive transfer request (signal that client is now in listening state)
 * before it tries to connect to client for data transfer.
 * So client sends the Transfer request using control connection fd
 *
*/
int Client::createDataConnection(int controlConnectionfd) {
	// @logging
	// logs("[CLIENT] : I am creating a new data Connection");

	// When PORT command is not explicitly used, default values are used.
	// @logging
	logv(getDataDumpReceiverPortNumber());
	int dataConnectionSocketfd =
		createSocketAndBindToPort(getDataDumpReceiverPortNumber());

	/**Listen
	 *
	 * we want to accept only 1 connection, i.e. of server
	 * No waiting connections are to be allowed.
	 *
	 * But setting backlog to 0 can lead to unpredicted errors,
	 * as it is implementation specific.
	*/
	Listen(dataConnectionSocketfd, 1);

	// client is now ready and is listening
	Send(controlConnectionfd, "Client Listening. Please Transfer.");

	// see if server needs any help with routing
	string serverResponse;
	Recv(controlConnectionfd, serverResponse);
	logs(serverResponse.c_str());

	string ipAddressOfDataServer;
	int dataConnectionfd;
	if (serverResponse.find("[RESPONSE] HELP ME") == 0) {  // server needs help
		logs("CLIENT HELP XXXXXXXXXXXXX");
		dataConnectionfd = provideHelpAndCreateDataConnection(controlConnectionfd);
	} else {  // server is ready
		// accept will only return when a connection is made.
		dataConnectionfd = Accept(dataConnectionSocketfd, ipAddressOfDataServer);
	}

	return dataConnectionfd;
}