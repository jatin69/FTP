#include "./../client.hpp"

/**STRU - structure change
 * 
 * FTP supports different types of data structures to be tranferred.
 * FILE (Default)
 * Record
 * PAGE Structure
 * 
*/
void Client::cmd_STRU(int controlConnectionfd, const vector<string>& args [[gnu::unused]]) {
    string ftpResponse;
    Recv(controlConnectionfd, ftpResponse);
    logs(ftpResponse.c_str());
}
