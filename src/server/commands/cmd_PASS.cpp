#include "./../server.hpp"

int Server::cmd_PASS(int controlConnectionfd, const vector<string> &args, const string& ftpUser) {

  string ftpPassword(args[1]);
  bool isAuthenticated = false;

  for (auto it : hashedUserPassTable) {
    if (oneWayHash(ftpUser) == it.first &&
        (oneWayHash(ftpPassword) == it.second)) {
        isAuthenticated = true;
        break;
    }
  }
  if (isAuthenticated) {
    Send(controlConnectionfd, "[AUTHENTICATION:SUCCESS] User logged in.", 230);
    return 1;
  } else {
    Send(controlConnectionfd, "[AUTHENTICATION:FAILURE] Retry");
    return 0;
  }
}
