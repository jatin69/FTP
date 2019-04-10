#include "./../server.hpp"

/**MODE
 * 
 * FTP has three modes :
 * Stream ( default )
 * Block
 * Compressed
 * 
 * Command not implemented yet.
*/
void Server::cmd_MODE(int controlConnectionfd, const vector<string>& args [[gnu::unused]]) {
    string response = "Hey there,\nMODE Change is not supported for now.\n";
    response.append("The Default transfer mode is - STREAM MODE.");
    Send(controlConnectionfd, response , 502);
}
