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
#define log(x) fprintf(stdout, "\n%s\n", x)

namespace FTP{
  const int LINE_SIZE = 1000;
  const int SOCKET_READ_BUFFER_SIZE = 10000;
  const int FILE_READ_BUFFER_SIZE = 100000;
  const string DELIM("\r\n");
  const int OFFSET_dataConnectionToClient = 10; // normally its 0
  const int OFFSET_dataConnectionToServer = 1; // normally its 1
}

// Print error messages
void printError(const char* msg = "No Detailed Info Available");
void printInfo(const char *msg);
void printInfo(const char *msg, int value);

void* _get_in_addr(struct sockaddr *sa);

// Socket programming functions
int createSocketAndConnectToHost(const char* host, int port);

// Create a socket and bind it to the given port
int createSocketAndBindToPort(int portNumber);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, string& ipAddressOfClient);

vector<string> commandTokenizer(string& cmd);

// API : dump data at remote IP
int handleDataDumpProcessAtRemoteIP();

class Client {
    private:
    
    //  Control IP : with whom the connection is Active
  string controlConnectionIP ;
  // Control port : Protocol Interpreter Connection Port
  const int controlConnectionPortNumber ;
  
  // Data Connection IP : By default it is same as controlConnectionIP
  // receive from which IP : Usually the server IP

  // this var is normally not in use
  // stringstream ferently when client wants the dump at a separate IP
  // then client will tell controlConnectionIP to dump at dataDumpReceiverIP
  string dataDumpReceiverIP ;

  // Data Connection Port Number : By default it is same as 1+controlConnectionPortNumber
  // receive on which port number 
  int dataDumpReceiverPortNumber ;

  // extraBuffer
  string extraBuffer = ""; 

    public:
    Client() :
      controlConnectionIP{""},
      controlConnectionPortNumber{9000},
      dataDumpReceiverIP{"CURRENT_MACHINE_IP"},
      dataDumpReceiverPortNumber{ controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient} {}

Client( 
    string _controlConnectionIP, 
    const int _controlConnectionPortNumber
    ) : 
      controlConnectionIP{_controlConnectionIP},
      controlConnectionPortNumber{_controlConnectionPortNumber},
      dataDumpReceiverIP{"CURRENT_MACHINE_IP"},
      dataDumpReceiverPortNumber{ controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient} {}

    
  /************************ Getters & Setters ***********************/
  
  const char* getControlConnectionIP() { return controlConnectionIP.c_str(); }
  int getControlConnectionPortNumber() { return controlConnectionPortNumber; }
  
  const char* getDataDumpReceiverIP() { return dataDumpReceiverIP.c_str(); }
  int getDataDumpReceiverPortNumber() { return dataDumpReceiverPortNumber; }
  
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
  void setDataDumpReceiverPortNumber(int _port) { dataDumpReceiverPortNumber = _port; }

  void resetDataDumpReceiverIP() { dataDumpReceiverIP = "CURRENT_MACHINE_IP";  }
  void resetDataDumpReceiverPortNumber() { 
    dataDumpReceiverPortNumber = controlConnectionPortNumber + FTP::OFFSET_dataConnectionToClient; }
  

  /**************************** loggers ****************************/
  void logClientConfiguration();

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

    // Internal Functions

    // Send the entire buffer
    int _send_all(int sockfd, const void *buffer, size_t length);
    // Send the complete file pointed by fd as binary data
    int _send_all_binary(int sockfd, FILE *fd, int size);

    // Receive data until socket is empty and save it to a string
    int _recv_all(int sockfd, string& result);
    // Receive binary data until socket is empty and save it to a file
    int _recv_all_binary(int sockfd, FILE *fd);


    // Protocol Interpreter for Client
    void initiateProtocolInterpreter(int connectionControlfd);

    // control connection is passed so it can convey the receiver of transfer request
    int createDataConnection(int controlConnectionfd);
    int provideHelpAndCreateDataConnection(int controlConnectionfd);
    
    ~Client() = default;

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
    TYPE, MODE, STRU,
    QUIT, ABOR
  };

  // Resolve command type
  Command resolveCommand(const string& incomingCommandTokens);

  string sanitizeRequest(const string& ftpRequest);

  // Wrappers to execute Commands
  void cmd_USER(int, const vector<string>&);
  void cmd_PASS(int, const vector<string>&);
  
  void cmd_PORT(int, const vector<string>& args = vector<string>());
  void cmd_LIST(int, const vector<string>& args = vector<string>());
  void cmd_CWD(int, const vector<string>&);
  void cmd_MKD(int, const vector<string>&);
  void cmd_RMD(int, const vector<string>&);
  void cmd_STOR(int, const vector<string>&);
  void cmd_RETR(int, const vector<string>&);
  void cmd_TYPE(int, const vector<string>&);
  void cmd_MODE(int, const vector<string>&);
  void cmd_STRU(int, const vector<string>&);
  
  void cmd_NOOP(int);
  void cmd_SYS(int);
  void cmd_PASV(int);
  void cmd_PWD(int);
  void cmd_QUIT(int);
  void cmd_ABOR(int);
  void cmd_INVALID(int);
  
};

#endif // !SRC_CLIENT_CLIENT_H
 