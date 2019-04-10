#include "./client.hpp"

// receive functions

/**Recv : wrapper for system call `recv`
 * 
 * @usage
 * Receives exactly one line (upto delim) from the socket.
 * If extra content is read, it is stored in `extraBuffer`
 * received line is reflected in `result` argument
 * 
 * @returns
 * 0 on success, -1 on error
 * 
 * @side-effect
 * the received one line is stored in `result` argument
*/
int Client::Recv(int sockfd, string& result) {
    
    char buffer[FTP::LINE_SIZE+1];
    int noOfBytesRead = 0;
	result = extraBuffer;

	do{
		result += string(buffer, buffer + noOfBytesRead);
		size_t pos = result.find(FTP::DELIM);
        if (pos != string::npos){   //found
			extraBuffer = result.substr(pos + FTP::DELIM.size());
			result = result.substr(0, pos + FTP::DELIM.size());
			break;
		}
	} while((noOfBytesRead = recv(sockfd, buffer, FTP::LINE_SIZE, 0)) > 0);

	if (noOfBytesRead < 0){
        printError("[RECV:LINE]");
		throw runtime_error("Error in Receiving");
	}
	
	return 0;
}

/**_recv_all : Internal function
 * 
 * @usage
 * receive everything present in the socket and reflects it as string
 * in `result`
 * 
 * @returns
 * total no of bytes received
 * 
 * @side-effect
 * the received data is stored in `result` argument
*/
int Client::_recv_all(int sockfd, string& result){

    int totalNoOfBytesReceived = 0;
    int noOfBytesRead = 1;

	while(noOfBytesRead != 0){

		char buffer[FTP::SOCKET_READ_BUFFER_SIZE+1];
		noOfBytesRead = recv(sockfd, buffer, FTP::SOCKET_READ_BUFFER_SIZE, 0);
        if( noOfBytesRead < 0){
            printError();
            return -1;
        }

		if(noOfBytesRead >0){
			result += std::string(buffer, buffer + noOfBytesRead);
			totalNoOfBytesReceived += noOfBytesRead;
		}
	}

    return totalNoOfBytesReceived;
}

/**RecvFile : Wrapped to receive a file
 * 
 * @usage
 * reads everything from buffer, then saves it as file
 * The end of file is determined by the closing of connection.
 * 
 * @returns
 * total no of bytes received
 * 
 * @side-effect
 * a new file is created with the specified `filename`
*/
int Client::RecvFile(int sockfd, const string& filename){
    FILE *filew;
	filew = fopen(filename.c_str(), "wb");
	int totalNoOfBytesReceived = _recv_all_binary(sockfd, filew);
    printInfo("Bytes Received : ", totalNoOfBytesReceived);
	fclose(filew);
    return totalNoOfBytesReceived;		
}

/**_recv_all_binary : Internal function
 * 
 * @usage
 * receive everything present in the socket and store it in given file descriptor
 * 
 * @returns
 * total no of bytes received
 * 
*/
int Client::_recv_all_binary(int sockfd, FILE* fd) {
    
    int totalNoOfBytesReceived = 0;
    int noOfBytesRead = 1;

	while(noOfBytesRead != 0){

		char buffer[FTP::SOCKET_READ_BUFFER_SIZE+1];
		noOfBytesRead = recv(sockfd, buffer, FTP::SOCKET_READ_BUFFER_SIZE, 0);
        if( noOfBytesRead < 0){
            printError();
            return -1;
        }

		if(noOfBytesRead > 0){
			fwrite(buffer, 1, noOfBytesRead, fd);
			totalNoOfBytesReceived += noOfBytesRead;
		}
	}
    return totalNoOfBytesReceived;
}

/**RecvWithTimeout : wrapper for system call `recv` with timeout support
 * 
 * @usage
 * listen on the `recv`, 
 * if data comes, execute standard `Recv`
 * if nothing comes after a specified time, timeout and return status
 *
 * @returns
 * 0 on success, -1 on error, 
 * -2 on timeout (developer-decided)
 * 
*/
int Client::RecvWithTimeout(int controlConnectionfd, string& transferRequest, int timeoutDurationInSeconds) {

	// set up the file descriptor set
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(controlConnectionfd, &fds);

	// set up the struct timeval for the timeout
	struct timeval tv;
	tv.tv_sec = timeoutDurationInSeconds;
	tv.tv_usec = 0;

	// wait until timeout or data received
	int n;
	n = select(controlConnectionfd+1, &fds, NULL, NULL, &tv);
	
	if (n == 0){	// timeout 
		return -2;		
	} 
	if (n == -1){	// error
		printError("[RECV:TIMEOUT:ERROR]");
		return -1;
	} 

	// data must be here, so do a normal Recv()
	return Recv(controlConnectionfd, transferRequest);
}
