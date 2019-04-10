#include "./../client.hpp"

/**ABOR - Abort
 * 
 * Abort the last command and any associated data transfer.
 * Usually used to kill the last data transfer (if ongoing).
 * 
 * Command not implemented yet.
*/
void Client::cmd_ABOR(int controlConnectionfd) { 
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
