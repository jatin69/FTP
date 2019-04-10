#include "./../client.hpp"

/**INVALID
 * 
 * Any user entered input, that is not matched 
 * with any FTP command is treated as invalid.
 * 
 * This also acts as a sink tester for new commands,
 * that exist on server, but not on client.
 * They can receive single response.
 * 
*/
void Client::cmd_INVALID(int controlConnectionfd) { 
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
