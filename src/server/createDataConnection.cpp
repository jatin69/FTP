#include "./server.hpp"

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
 *
*/
int Server::createDataConnection(int controlConnectionfd) {
	// @logging
	logs("[SERVER] : I am creating a new data Connection");

	const char* ip = getDataConnectionIP();
	int port = getDataConnectionPortNumber();

	// this is also a race condtion, resolve it
	bool doesRouteExist = doesRouteToHostExist(ip, port);

	// @logging
	logServerConfiguration();

	/**Special Note : Race Condition Resolving
	 *
	 * It is extremely important that we try to connect only after the
	 * client has started listening.
	 *
	 * To ensure this, we try to take measures.
	 *
	 * sleep(1)
	 * we delay the server by sleeping it for 1 second.
	 * But this is not full proof. If the client is so slow that it takes
	 * more than one second to start listening,
	 * our this code will crash.
	 *
	 * sleep(3)
	 * We can delay the server by 3 seconds to ensure that
	 * client will be listening, but this increases response time to 3+ seconds,
	 * which is very much.
	 *
	 * Solution :
	 * We implement a transfer request as stated in RFC-959
	 * Recv() is a blocking call, so it'll wait until transfer request comes up.
	 *
	*/

	string transferRequest;
	int timeOutDurationInSeconds = 3;
	int stat =
		RecvWithTimeout(controlConnectionfd, transferRequest, timeOutDurationInSeconds);
	if (stat == -2) {
		logs("TIMEOUT OCCURRED. No Transfer Request Received from Client.");
		exit(-2);
	}

	int dataConnectionfd;
	
	// @logging
	logv(doesRouteExist);

	if (doesRouteExist) {
		Send(controlConnectionfd, "I AM READY");
		dataConnectionfd = createSocketAndConnectToHost(ip, port);
	} else {
		Send(controlConnectionfd, "HELP ME");
		dataConnectionfd = askForHelpAndCreateDataConnection(controlConnectionfd);
	}

	return dataConnectionfd;
}