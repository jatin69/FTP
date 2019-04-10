#ifndef SRC_CLIENT_CLIENT_H
#define SRC_CLIENT_CLIENT_H

/************************** Header Files *************************/

// Standard
#include <iostream>
#include <string>
#include <sstream>

#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// STL 
#include <algorithm>
#include <vector>
#include <functional>

// socket programming
#include <sys/socket.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <locale>
#include <arpa/inet.h>
#include <dirent.h>

// signal handling
#include <signal.h>
#include <execinfo.h>

// standard namespace
using namespace std;

/****************** Constants, Preprocessors, Namespaces ******************/

// Preprocessors
#define logs(x) fprintf(stdout, "\n[LOGGING] %s\n", x)
#define logv(x) cout << "[Variable] " << #x << " = " << x << "\n"

namespace FTP{
  const int LINE_SIZE = 1000;
  const int SOCKET_READ_BUFFER_SIZE = 10000;
  const int FILE_READ_BUFFER_SIZE = 100000;
  const string DELIM("\r\n");
  const string CLIENT_SIDE_COMMAND_IDENTIFIER("!");


  /**[1] : Data Connection offset is set to 10
   * 
   * This is normally 0. That means,
   * the data connection port is same as the control connection port
   * in the default mode.
   * 
   * But this can't be done on localhost,
   * because same port can't be binded to same src-dest address pair twice
   * 
  */
  const int OFFSET_dataConnectionToClient = 10; // normally its 0
  const int OFFSET_dataConnectionToServer = 1; // normally its 1
}

/************************** General purpose functions *************************/

// Print error messages
void printError(const char* msg = "No Detailed Info Available");
void printInfo(const char *msg);
void printInfo(const char *msg, int value);

// utils
vector<string> commandTokenizer(string& cmd);
string &trim(string &s);

// execute shell command
string executeShellCommand(const string&);

/************************** Socket programming functions *************************/

// Create a socket and bind it to the given port
int createSocketAndBindToPort(int portNumber);

// start listening on the given socket
void Listen(int sockfd, int backlog);

// accept & tell the ip Address of connected Client
int Accept(int sockfd, string& ipAddressOfClient);

// create a socket and connect to specified host on his specified port
int createSocketAndConnectToHost(const char* host, int port);

// print IP address from the given socket address structure
void get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen);

// API : dump data at remote IP
int handleDataDumpProcessAtRemoteIP();


/************************** CLIENT CLASS *************************/

/** Class : Client
 *
 * A simple class to encapsulate all client related features.
*/
class Client {

  /**Note that
   * 
   * The ftp client object only connects to one server in its lifetime,
   * It can therefore, be used to store information about its connection 
   * with the server
  */

private:
    
  //  Control IP : with whom the connection is Active
  string controlConnectionIP ;
  
  // Control port : Protocol Interpreter Connection Port
  const int controlConnectionPortNumber ;
  
  // IP address of machine which wants to receive data
  // by default this machine is the same machine which establishes control connection
  string dataDumpReceiverIP ;

  // Port at which the receiver machine wants to receive data
  // By default it is same as control connection port no (refer [1])
  int dataDumpReceiverPortNumber ;

  // extraBuffer : if recv reads up extra after newline, it is kept here
  string extraBuffer = ""; 


  /************************ private member functions ***********************/

  // Data Send / Receive Internal Functions

  // Send the entire buffer
  int _send_all(int sockfd, const void *buffer, size_t length);

  // Send the complete file pointed by fd as binary data
  int _send_all_binary(int sockfd, FILE *fd, int size);

  // Receive data until socket is empty and save it to a string
  int _recv_all(int sockfd, string& result);

  // Receive binary data until socket is empty and save it to a file
  int _recv_all_binary(int sockfd, FILE *fd);

public:

  /************************ Cons'tors & Des'tors ***********************/
  
  // Default constructor
  Client() :
    controlConnectionIP{""},
    controlConnectionPortNumber{9000},
    dataDumpReceiverIP{"CURRENT_MACHINE_IP"},
    dataDumpReceiverPortNumber{ controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient} {}

  // Paramterized constructor
  Client( 
    string _controlConnectionIP, 
    const int _controlConnectionPortNumber
    ) : 
      controlConnectionIP{_controlConnectionIP},
      controlConnectionPortNumber{_controlConnectionPortNumber},
      dataDumpReceiverIP{"CURRENT_MACHINE_IP"},
      dataDumpReceiverPortNumber{ controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient} {}

  // Default destructor
  ~Client() = default;
    
  /************************ Getters & Setters ***********************/
  
  // control connection IP
  const char* getControlConnectionIP() { return controlConnectionIP.c_str(); }

  // control connection port number
  int getControlConnectionPortNumber() { return controlConnectionPortNumber; }
  
  // data dump receiver IP
  const char* getDataDumpReceiverIP() { return dataDumpReceiverIP.c_str(); }
  void setDataDumpReceiverIP(string _IP) {  
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
      
    dataDumpReceiverIP = _IP;
      
  }  
  void resetDataDumpReceiverIP() { dataDumpReceiverIP = "CURRENT_MACHINE_IP";  }
  
  // data dump deceiver port number
  int getDataDumpReceiverPortNumber() { return dataDumpReceiverPortNumber; }
  void setDataDumpReceiverPortNumber(int _port) { dataDumpReceiverPortNumber = _port; }
  void resetDataDumpReceiverPortNumber() { 
    dataDumpReceiverPortNumber = controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient; }
  
  /**************************** loggers ****************************/
  
  void logClientConfiguration();

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
  
  // Protocol Interpreter for Client
  void initiateProtocolInterpreter(int connectionControlfd);

  // Authentication
  int authenticateFromServer(int controlConnectionfd);

  // Data Connection : server establishes connection to client
  int createDataConnection(int controlConnectionfd);
  int provideHelpAndCreateDataConnection(int controlConnectionfd);
    

  /************************ Supported Commands ****************************/

  // Supported Commands 
  enum Command {
    INVALID, CLIENT,
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

  // sanitize user request
  string sanitizeRequest(const string& ftpRequest);

  // Resolve command type
  Command resolveCommand(const string& incomingCommandTokens);

  // Wrappers to execute Commands
  void cmd_CLIENT(const string&);

  void cmd_USER(int, const vector<string>&);
  int cmd_PASS(int, const vector<string>&);
  
  void cmd_PORT(int, const vector<string>&);
  void cmd_LIST(int, const vector<string>&);
  void cmd_STOR(int, const vector<string>&);
  void cmd_RETR(int, const vector<string>&);
  void cmd_CWD(int,  const vector<string>&);
  void cmd_MKD(int,  const vector<string>&);
  void cmd_RMD(int,  const vector<string>&);
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

#endif // !SRC_CLIENT_CLIENT_H