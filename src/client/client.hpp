#ifndef SRC_CLIENT_CLIENT_H
#define SRC_CLIENT_CLIENT_H


/** Header Files
 *
*/
#include <algorithm>
#include <vector>
#include <arpa/inet.h>
#include <arpa/inet.h> // inet_pton
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <errno.h>
#include <functional>
#include <iostream>
#include <locale>
#include <netdb.h>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> // close()
#include <signal.h>
using namespace std;

// Preprocessors
#define logv(x) cout << "[Variable] " << #x << " = " << x << "\n"
#define logs(x) fprintf(stdout, "\n[LOGGING] %s\n", x)

namespace FTP{
  const int LINE_SIZE = 1000;
  const int SOCKET_READ_BUFFER_SIZE = 10000;
  const int FILE_READ_BUFFER_SIZE = 100000;
  const string DELIM("\r\n");
}

// Print error messages
void printError(const char* msg = "No Detailed Info Available");
void printInfo(const char *msg);
void printInfo(const char *msg, int value);

void* _get_in_addr(struct sockaddr *sa);

// Socket programming functions
int createSocketAndConnectToHost(const char* host, int port);

class Client {
    private:
    
    // Public Internet IP address of server we want to connect to
    const char* serverIP;

    // To Which server port should the connection be established
    int serverPort;

    // Should the client be verbose and print all internal messages
    bool isVerboseModeOn;

      // extraBuffer
    string extraBuffer;

    // Internal Functions

    // Send the entire buffer
    int _send_all(int sockfd, const void *buffer, size_t length);
    // Send the complete file pointed by fd as binary data
    int _send_all_binary(int sockfd, FILE *fd, int size);

    // Receive data until socket is empty and save it to a string
    int _recv_all(int sockfd, string& result);
    // Receive binary data until socket is empty and save it to a file
    int _recv_all_binary(int sockfd, FILE *fd);


    public:
    Client() :
      serverIP{"127.0.0.1"},
      serverPort{9000},
      isVerboseModeOn{true},
      extraBuffer{""} {}

    Client(
      const char* _serverIP = "127.0.0.1", 
      int _serverPort = 9000, 
      bool _isVerboseModeOn = true,
      string _extraBuffer = ""
      )  :
         serverIP(_serverIP),
         serverPort(_serverPort),
         isVerboseModeOn(_isVerboseModeOn),
         extraBuffer{_extraBuffer} {}
    
    // getters
    bool isVerbose() { return isVerboseModeOn; }
    const char* getServerIP() { return serverIP; }
    int getServerPortNumber() { return serverPort; }

    // functions

      /************ Wrappers for Sending and Receiving Data **************/

  // Send ONE LINE
  int Send(int sockfd, const string& msgToSend, int responseCode = 0);

  // Receive ONE LINE
  int Recv(int sockfd, string& msgReceived);
  
  // Send the file `filename` through the socket as binary data
  int SendFile(int sockfd, const string& filename);  
  
  // Receive the file from the socket and save it with name `filename`
  int RecvFile(int sockfd, const string& filename);


    // Protocol Interpreter for Client
    void initiateProtocolInterpreter(int connectionControlfd);


    ~Client() = default;
};

#endif // !SRC_CLIENT_CLIENT_H
 