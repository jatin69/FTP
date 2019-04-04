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
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h> // close()
#include <signal.h>
#include <execinfo.h>
using namespace std;

// Preprocessors
#define log(x) fprintf(stdout, "%s\n", x)
#define logv(x) cout << "[Variable] " << #x << " = " << x << "\n"
#define logs(x) fprintf(stdout, "[LOGGING] %s\n", x)
#define logr(x) cout << "[REQUEST] " << #x << " = " << x << "\n"

namespace FTP{
  const int LINE_SIZE = 1000;
  const int SOCKET_READ_BUFFER_SIZE = 10000;
  const int FILE_READ_BUFFER_SIZE = 100000;
  const string DELIM("\r\n");

  /**These two cant be same for localhost
   * Unfortunately, for localhost these cant be same.
   * Because its the same machine. Same port can't be reused on same address.
  */
  const int OFFSET_dataConnectionToClient = 10; // normally its 0
  const int OFFSET_dataConnectionToServer = 1; // normally its 1
}

// The following functions doesn't need to be part of the class
// These are general Socket Programming functions
// They follow Beej's advices

// UTILS
vector<string> commandTokenizer(string& cmd);
vector<string> pathTokenizer(string& path);
string oneWayHash(string s);

// ftpUser ftpPassword table
extern vector<pair<string, string>> hashedUserPassTable ;

// Print error messages
void printError(const char* msg = "No Detailed Info Available");
void printInfo(const char *msg);
void printInfo(const char *msg, int value);

void* _get_in_addr(struct sockaddr *sa);

// Socket programming functions
int createSocketAndConnectToHost(const char* host, int port);
bool doesRouteToHostExist(const char* host, int portNumber);

// Create a socket and bind it to the given port
int createSocketAndBindToPort(int portNumber);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, string& ipAddressOfClient);

string executeShellCommand(const string&);

/** Class : Server
 *
 * A simple class to encapsulate all server related features
*/
class Server {

  private:
  
  //  Control IP : with whom the connection is Active
  string controlConnectionIP ;
  // Control port : Protocol Interpreter Connection Port
  const int controlConnectionPortNumber ;
  
  // Data Connection IP : By default it is same as controlConnectionIP
  
  // send data from which IP
  string dataConnectionIP ;
  
  // send data to which port : in default cases, we send to client control port only
  int dataConnectionPortNumber;

  // ignore this comment
  // Data Connection Port Number : By default it is same as 1+controlConnectionPortNumber

  // When accept() call is blocking, how many potential connections are allowed to queue up
  const int backlogsPermitted ;

  // extraBuffer
  string extraBuffer = "";

  // stored username
  string clientUsername = "";

  // auth status
  bool isClientAuthenticated = false;

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
    controlConnectionIP{""},
    controlConnectionPortNumber{9000},
    dataConnectionIP{controlConnectionIP},
    dataConnectionPortNumber{controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient},
    backlogsPermitted{10} {}

  // Paramterized cons'
  Server(
    const int _controlConnectionPortNumber,
    int _backlogsPermitted = 10
    ) : 
      controlConnectionIP{""},
      controlConnectionPortNumber{_controlConnectionPortNumber},
      dataConnectionIP{controlConnectionIP},
      dataConnectionPortNumber{controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient},
      backlogsPermitted{_backlogsPermitted} {}

  ~Server() = default;
  

  /************************ Getters & Setters ***********************/
  int getBacklogsPermitted() { return backlogsPermitted; }
  
  const char* getControlConnectionIP() { return controlConnectionIP.c_str(); }
  int getControlConnectionPortNumber() { return controlConnectionPortNumber; }
  void setControlConnectionIP(const char* _IP) { 
    controlConnectionIP= _IP; 
    dataConnectionIP = controlConnectionIP; 
  }
  
  const char* getDataConnectionIP() { return dataConnectionIP.c_str(); }
  int getDataConnectionPortNumber() { return dataConnectionPortNumber; }
  
  void setDataConnectionIP(string _IP) {
    transform(_IP.begin(), _IP.end(), _IP.begin(), ::toupper);

    /**Handling naive user
     * 
     * When user uses 127.0.0.1 or localhost as dumping site.
     * He is being naive.
     * User is trying to dump to his machine but he doesn't know 
     * he has to use CURRENT_MACHINE_IP for this.
     * 
     * NO problem, we'll forgive him, for NOW
    */
    if( string("127.0.0.1").compare(_IP) == 0 || string("LOCALHOST").compare(_IP) == 0 ) {
      _IP = "CURRENT_MACHINE_IP";
    }
    
    if(string("CURRENT_MACHINE_IP").compare(_IP) == 0 ) {
      resetDataConnectionIP();
    }
    else{
      dataConnectionIP = _IP;
    }
  }  
  void setDataConnectionPortNumber(int _port) { dataConnectionPortNumber = _port; }

  void resetDataConnectionIP() { dataConnectionIP = controlConnectionIP;  }
  void resetDataConnectionPortNumber() { 
    dataConnectionPortNumber = controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient; 
  }

  bool getClientAuthenticationStatus() {
    return isClientAuthenticated;
  }

  void updateClientAuthenticationStatus(bool status) {
    isClientAuthenticated = status;
  }

  string getClientUsername() {
    return clientUsername;
  }

  void setClientUsername(string _username) {
    clientUsername = _username;
  }
  
  void resetClientUsername() {
    clientUsername = "";
  }
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
  int RecvWithTimeout(int controlConnectionfd, string& transferRequest, int timeoutDurationInSeconds);
  
  // Send the file `filename` through the socket as binary data
  int SendFile(int sockfd, const string& filename);  
  
  // Receive the file from the socket and save it with name `filename`
  int RecvFile(int sockfd, const string& filename);


  /**************************** FTP functions ****************************/

  // Protocol Interpreter for Server
  void initiateProtocolInterpreter(int connectionControlfd);

  // control connection is passed so it can received transfer request
  int createDataConnection(int controlConnectionfd);
  int askForHelpAndCreateDataConnection(int controlConnectionfd);

  // Authentication
  void authenticateClient(int controlfd);

  /**************************** FTP Commands ****************************/

  // Supported Commands by Server
  enum Command {
    INVALID,
    USER, PASS,
    NOOP, SYS,
    PORT, PASV,
    LIST, PWD,
    CWD, CDUP,
    MKD, RMD,
    STOR, RETR,
    TYPE, MODE, STRU,
    QUIT, ABOR
  };

  // Resolve command type
  Command resolveCommand(const string& incomingCommandTokens);

  // Wrappers to execute Commands
  void cmd_USER(int, const vector<string>&);
  void cmd_PASS(int, const vector<string>&);
  
  void cmd_PORT(int, const vector<string>&);
  void cmd_LIST(int, const vector<string>&);
  void cmd_CWD(int, const vector<string>&);
  void cmd_MKD(int, const vector<string>&);
  void cmd_RMD(int, const vector<string>&);
  void cmd_STOR(int, const vector<string>&);
  void cmd_RETR(int, const vector<string>&);
  void cmd_TYPE(int, const vector<string>&);
  void cmd_MODE(int, const vector<string>&);
  void cmd_STRU(int, const vector<string>&);
  
  void cmd_NOOP(int);
  void cmd_CDUP(int);
  void cmd_SYS(int);
  void cmd_PASV(int);
  void cmd_PWD(int);
  void cmd_QUIT(int);
  void cmd_ABOR(int);
  void cmd_INVALID(int);
  
};

#endif // !SRC_SERVER_SERVER_H

// @todo
// 1. Move constructor?
