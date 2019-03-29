#include "./client.hpp"

// @todo : document
// this is done to support IPv6 

int Accept(int sockfd, string& ipAddressOfClient) {

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
  fprintf(stdout, "[CLIENT]: Got connection from %s", s);
  ipAddressOfClient = s;

  return connectionControlfd;
}
