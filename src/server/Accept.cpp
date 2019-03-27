#include "./server.hpp"

// @todo : document
// this is done to support IPv6 

void* _get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int Accept(int sockfd) {

  // connector's address information
  struct sockaddr_storage their_addr;
  char s[INET6_ADDRSTRLEN];
  socklen_t sin_size = sizeof their_addr;

  // Accept connections
  int connectionControlfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
  if (connectionControlfd == -1) {
    printError();
    return -1;
  }

  /**inet_ntop : Convert IP addresses to human-readable form and back.
   * 
  */
  inet_ntop(their_addr.ss_family, _get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
  fprintf(stdout, "[SERVER]: Got connection from %s", s);

  return connectionControlfd;
}
