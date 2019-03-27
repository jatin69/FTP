#include "./client.hpp"

// @todo : Document

// Send ONE LINE
int Client::Send(int sockfd, const string& msgToSend, int responseCode) {
    string msg;
    if(responseCode != 0){
        msg += string("[Request : ") + to_string(responseCode) + string("] "); 
    }
    msg += msgToSend;
    msg += FTP::DELIM;
    // logs(msg.c_str());
    return _send_all(sockfd, msg.c_str(), msg.size());
}

// Send the entire buffer
int Client::_send_all(int sockfd, const void *buffer, size_t length) {
    size_t totalNumberBytesSent = 0;
    while(totalNumberBytesSent < length){
        int noOfBytesSent = send(sockfd, buffer, length - totalNumberBytesSent, MSG_NOSIGNAL);
        if(noOfBytesSent == -1){
            printError("[SEND]");
            break;
        }
        totalNumberBytesSent += noOfBytesSent;
    }

    if(totalNumberBytesSent < length) { 
        return -1; 
    }

    return 0;
}

// Send a file
int Client::SendFile(int sockfd, const string& filename) {
    struct stat st;
    int statcode = stat(filename.c_str(), &st);
	if(statcode == -1){
        return -1;
    }
    
    int size = st.st_size;

    FILE *file;
    file = fopen(filename.c_str(), "rb");
    size_t noOfBytesSent = _send_all_binary(sockfd, file, size);
    printInfo("Bytes Sent : ", noOfBytesSent);
    fclose(file);

    return 0;
}

// Send the complete file pointed by fd as binary data
int Client::_send_all_binary(int sockfd, FILE *fd, int sizeOfFile){
    unsigned char buffer[FTP::FILE_READ_BUFFER_SIZE+1];
	int bytesSent=0;
	
    while(sizeOfFile > 0){
        int noOfBytesRead = fread(buffer, 1, FTP::FILE_READ_BUFFER_SIZE, fd);
		int status = _send_all(sockfd, buffer, noOfBytesRead);
		if(status != 0 ){
            printError("[SEND-BINARY]");
			break;
		}
		sizeOfFile -= noOfBytesRead;
	}
    if(sizeOfFile > 0){
        return -1;
    }
	return 0;	
}
