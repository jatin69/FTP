#include "./../server.hpp"

/**PORT command
 *
 * @usage
 * sets new Data connection IP and PORT for the next command
*/
void Server::cmd_PORT(int controlConnectionfd, const vector<string>& args) {
	string IP;
	int PORT;

	// @todo
	/**PORT Command format
	 *
	 * Actually, the port command has a comma format during the transfer.
	 * But for simplicity here, we have hold on to original format
	 * for transfer as well.
	 *
	 * We can implement comma format if needed,
	 * encode port string on client side and decode it on the server side.
	 *
	 * resolvePortCommandString(IP, PORT);
	 *
	*/
	IP = args[1];
	PORT = atoi(args[2].c_str());

	setDataConnectionIP(IP);
	setDataConnectionPortNumber(PORT);

	string res("PORT Command Successful.");
	res += "\nNew Data IP is : " + string(getDataConnectionIP());
	res += "\nNew Data Port is : " + to_string(getDataConnectionPortNumber());

	// @logging
	// logServerConfiguration();

	Send(controlConnectionfd, res, 200);
}
