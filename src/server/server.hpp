#ifndef SRC_SERVER_SERVER_H
#define SRC_SERVER_SERVER_H

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
#define logs(x) fprintf(stdout, "[LOGGING] %s\n", x)

namespace FTP{
  const int LINE_SIZE = 1000;
  const int SOCKET_READ_BUFFER_SIZE = 10000;
  const int FILE_READ_BUFFER_SIZE = 100000;
  const string DELIM("\r\n");
}

// The following functions doesn't need to be part of the class
// These are general Socket Programming functions
// They follow Beej's advices

// UTILS
vector<string> commandTokenizer(string& cmd);

// Print error messages
void printError(const char* msg = "No Detailed Info Available");
void printInfo(const char *msg);
void printInfo(const char *msg, int value);

void* _get_in_addr(struct sockaddr *sa);

// Create a socket and bind it to the given port
int createSocketAndBindToPort(int portNumber);
void Listen(int sockfd, int backlog);
int Accept(int sockfd);

/** Class : Server
 *
 * A simple class to encapsulate all server related features
*/
class Server {

  private:
  
  // Control port : Protocol Interpreter Connection Port
  const int controlPortNumber;
  
  // data Connection Port : Used for data connections
  int dataConnectionPortNumber;

  // Should the Server be verbose and print all internal messages
  bool isVerboseModeOn;

  // When accept() call is blocking, how many potential connections are allowed to queue up
  const int backlogsPermitted;

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

  // Default cons'
  Server() :
    controlPortNumber{9000},
    dataConnectionPortNumber{9001},
    isVerboseModeOn{true},
    backlogsPermitted{10},
    extraBuffer{""}
    {}

  // Paramterized cons'
  Server(
    const int _controlPortNumber, 
    int _dataConnectionPortNumber = -1,
    bool _isVerboseModeOn = true,
    int _backlogsPermitted = 10,
    string _extraBuffer = ""
    ) : 
      controlPortNumber(_controlPortNumber),
      dataConnectionPortNumber(_dataConnectionPortNumber == -1 ? controlPortNumber + 1 : _dataConnectionPortNumber),
      isVerboseModeOn(_isVerboseModeOn),
      backlogsPermitted(_backlogsPermitted),
      extraBuffer(_extraBuffer) { }
  

  ~Server() = default;
  

  /**************************** Getters ****************************/

  bool isVerbose() { return isVerboseModeOn; }
  int getControlPortNumber() { return controlPortNumber; }
  int getBacklogsPermitted() { return backlogsPermitted; }


  /**************************** loggers ****************************/
  void logServerConfiguration();


  /***************** Wrappers for Socket Programming ****************/

  int Socket();
  void Bind(int sockfd, int port);
  int Connect(int sockfd, const std::string &host, int port);


  /************ Wrappers for Sending and Receiving Data **************/

  // Send ONE LINE
  int Send(int sockfd, const string& msgToSend, int responseCode = 0);

  // Receive ONE LINE
  int Recv(int sockfd, string& msgReceived);
  
  // Send the file `filename` through the socket as binary data
  int SendFile(int sockfd, const string& filename);  
  
  // Receive the file from the socket and save it with name `filename`
  int RecvFile(int sockfd, const string& filename);


  /**************************** FTP functions ****************************/

  // Protocol Interpreter for Server
  void initiateProtocolInterpreter(int connectionControlfd);

  // Authentication
  int authenticateClient(int controlfd);


  /**************************** FTP Commands ****************************/

  // Supported Commands by Server
  enum Command {
    INVALID,
    USER, PASS,
    NOOP, SYS,
    PORT, PASV,
    LIST, PWD,
    CWD, 
    MKD, RMD,
    STOR, RETR,
    QUIT, ABOR
  };

  // Resolve command type
  Command resolveCommand(const std::string& incomingCommand);

  // Wrappers to execute Commands
  void cmd_INVALID(int);
  void cmd_USER();
  void cmd_PASS();
  void cmd_NOOP(int);
  void cmd_SYS();
  void cmd_PORT();
  void cmd_PASV();
  void cmd_LIST();
  void cmd_PWD();
  void cmd_CWD();
  void cmd_MKD();
  void cmd_RMD();
  void cmd_STOR();
  void cmd_RETR();
  void cmd_QUIT();
  void cmd_ABOR();

};

#endif // !SRC_SERVER_SERVER_H

// @todo
// 1. Move constructor?
