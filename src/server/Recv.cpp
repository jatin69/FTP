#include "./server.hpp"

// @todo : Document

// read ONE LINE from Buffer 
// extra read part is kept in extraBuffer
int Server::Recv(int sockfd, string& result) {
    
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
		return -1;
	}
	
	return 0;
}

// Receive data until socket is empty and save it to a string
int Server::_recv_all(int sockfd, string& result){

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

// Receive a file and save it with filename
int Server::RecvFile(int sockfd, const string& filename){
    FILE *filew;
	filew = fopen(filename.c_str(), "wb");
	int totalNoOfBytesReceived = _recv_all_binary(sockfd, filew);
    printInfo("Bytes Received : ", totalNoOfBytesReceived);
	fclose(filew);
    return totalNoOfBytesReceived;		
}

// Receive binary data until socket is empty and save it to a file
int Server::_recv_all_binary(int sockfd, FILE* fd) {
    
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

// Recv with timeout

int Server::RecvWithTimeout(int controlConnectionfd, string& transferRequest, int timeoutDurationInSeconds) {
	fd_set fds;
	int n;
	struct timeval tv;
	// set up the file descriptor set
	FD_ZERO(&fds);
	FD_SET(controlConnectionfd, &fds);
	// set up the struct timeval for the timeout
	tv.tv_sec = timeoutDurationInSeconds;
	tv.tv_usec = 0;
	// wait until timeout or data received

	n = select(controlConnectionfd+1, &fds, NULL, NULL, &tv);
	
	if (n == 0){	// timeout 
		return -2;		
	} // timeout!
	if (n == -1){	// error
		printError("[RECV:TIMEOUT:ERROR]");
		return -1;
	} 

	// data must be here, so do a normal recv()
	return Recv(controlConnectionfd, transferRequest);
}