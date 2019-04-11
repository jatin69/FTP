#include "./../client.hpp"

/**MODE
 *
 * FTP has three modes :
 * Stream ( default )
 * Block
 * Compressed
 *
*/
void Client::cmd_MODE(int controlConnectionfd,
					  const vector<string>& args[[gnu::unused]]) {
	string ftpResponse;
	Recv(controlConnectionfd, ftpResponse);
	logs(ftpResponse.c_str());
}
