#include "./../client.hpp"

/**PASV
 * 
 * This command tells server to "listen" on his data port rather than
 * initiate a connection when he receives a transfer service command.
 * 
 * Command not implemented yet.
*/
void Client::cmd_PASV(int controlConnectionfd) { 
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
