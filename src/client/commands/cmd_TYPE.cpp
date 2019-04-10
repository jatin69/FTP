#include "./../client.hpp"

/**TYPE command
 * 
 * FTP Supports a number of types.
 * ASCII (Default) + NON PRINT (default)
 * EBCDIC TYPE
 * IMAGE TYPE
 * LOCAL TYPE
 * 
*/
void Client::cmd_TYPE(int controlConnectionfd, const vector<string>& args  [[gnu::unused]]) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
