#include "./client.hpp"

void printError(const char *msg) {
  int saveErrNo = errno;
  fprintf(
    stderr, 
    "\n[ERROR] : %s \n[ERROR code %d ] : %s\n ", 
    msg,
    saveErrNo,
    strerror(saveErrNo)
);
}

void printInfo(const char *msg) {
  fprintf( 
    stdout,
    "\n[INFO] : %s\n",
    msg
  );
}

void printInfo(const char *msg, int value) {
  printInfo((string(msg) + to_string(value)).c_str());
}