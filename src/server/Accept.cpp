#include "./server.hpp"

/**Accept - Wrapper function for `accept`
 * 
 * @usage
 * accepts incoming connection on the specified sockfd
 * 
 * @side-effect
 * prints out the accepted client's IP address
 * and reflects it back to `ipAddressOfClient` argument.
*/
int Accept(int sockfd, string& ipAddressOfClient) {

  // connector's address information
  struct sockaddr_storage their_addr;
  socklen_t sin_size = sizeof their_addr;

  // Accept connections
  int connectionControlfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
  if (connectionControlfd == -1) {
    printError();
    return -1;
  }

  // Print out IP address
  char s[INET6_ADDRSTRLEN];
  get_ip_str((const struct sockaddr *) &their_addr, s, sizeof s);
  fprintf(stdout, "[CLIENT]: Got connection from %s", s);

  ipAddressOfClient = s;
  return connectionControlfd;
}
