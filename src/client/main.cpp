#include "./client.hpp"

Client parseArgs(int, char**);
void segmentationFaultHandler(int sig); 

int main(int argc, char **argv) {

    // segmentation fault handler
    signal(SIGSEGV, segmentationFaultHandler); 

    // create a FTP client
    Client ftpClient = parseArgs(argc, argv);

    // create a socket and connect to Server
    int controlConnectionfd = createSocketAndConnectToHost(
        ftpClient.getControlConnectionIP(),
        ftpClient.getControlConnectionPortNumber()
    );

    // log client info
    ftpClient.logClientConfiguration();

    // Start the FTP protocol
    ftpClient.initiateProtocolInterpreter(controlConnectionfd);

    return 0;
} 


void segmentationFaultHandler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}