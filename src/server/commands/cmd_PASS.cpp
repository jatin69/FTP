#include "./../server.hpp"

// PASS - accepts password and authenticates the USER

void Server::cmd_PASS(int controlConnectionfd, const vector<string> &args) {

  string ftpUser(getClientUsername());
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
    updateClientAuthenticationStatus(true);
  } else {
    Send(controlConnectionfd, "[AUTHENTICATION:FAILURE] Retry");
    resetClientUsername();
  }
}
