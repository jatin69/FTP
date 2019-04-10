#include "./server.hpp"

/**Listen : Wrapper for `listen`
 * 
*/
void Listen(int sockfd, int backlog) {
  const int res = listen(sockfd, backlog);
  if (res < 0) {
    printError("[SERVER] : Failed to listen");
    throw std::runtime_error("Exiting : failed to listen");
  }
}
