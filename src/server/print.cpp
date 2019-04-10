#include "./server.hpp"

/**print Error Message
 * 
 * print the string version of `errno` along with user's custom message
*/
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
 
/**print Info
 * 
 * print user's custom message
*/
void printInfo(const char *msg) {
  fprintf(
    stdout,
    "\n[INFO] : %s\n",
    msg
  );
}

/**print Info : overloaded
 * 
 * print user's custom message with a value
*/
void printInfo(const char *msg, int value) {
  printInfo((string(msg) + to_string(value)).c_str());
}
