#include "./server.hpp"

/**Protocol Interpretor for server
 *
 * Classic FTP has two parts.
 * The PI to interpret commands, and the data connection to transfer files.
 *
*/
void Server::initiateProtocolInterpreter(int controlConnectionfd) {
	// begin
	Send(controlConnectionfd, "J's FTP-Server ");

	// authentication
	authenticateClient(controlConnectionfd);
	if (getClientAuthenticationStatus() == false) {
		cmd_QUIT(controlConnectionfd);
		return;
	}

	/**Previous command tracking
	 *
	 * PORT command changes the datadump site for the next command only.
	 * So we track the previous command, and reset the dump site after one command
	 *
	*/
	Command previousCommand = Command::INVALID;
	Command currentCommand = Command::INVALID;

	// command interpreter loop
	while (true) {
		// receive command from client
		string commandString;
		Recv(controlConnectionfd, commandString);
		// @logging
		fprintf(stdout, "\n[INFO][REQUEST] : %s", commandString.c_str());

		// tokenize command
		vector<string> tokens = commandTokenizer(commandString);

		// resolve command type from first word
		Command commandType = resolveCommand(tokens.front());

		switch (commandType) {
			case Command::PORT: {
				cmd_PORT(controlConnectionfd, tokens);
			} break;
			case Command::LIST: {
				cmd_LIST(controlConnectionfd, tokens);
			} break;
			case Command::CWD: {
				cmd_CWD(controlConnectionfd, tokens);
			} break;
			case Command::MKD: {
				cmd_MKD(controlConnectionfd, tokens);
			} break;
			case Command::RMD: {
				cmd_RMD(controlConnectionfd, tokens);
			} break;
			case Command::STOR: {
				cmd_STOR(controlConnectionfd, tokens);
			} break;
			case Command::RETR: {
				cmd_RETR(controlConnectionfd, tokens);
			} break;
			case Command::TYPE: {
				cmd_TYPE(controlConnectionfd, tokens);
			} break;
			case Command::MODE: {
				cmd_MODE(controlConnectionfd, tokens);
			} break;
			case Command::STRU: {
				cmd_STRU(controlConnectionfd, tokens);
			} break;
			case Command::NOOP: {
				cmd_NOOP(controlConnectionfd);
			} break;
			case Command::SYS: {
				cmd_SYS(controlConnectionfd);
			} break;
			case Command::CDUP: {
				cmd_CDUP(controlConnectionfd);
			} break;
			case Command::PWD: {
				cmd_PWD(controlConnectionfd);
			} break;
			case Command::QUIT: {
				cmd_QUIT(controlConnectionfd);
			} break;
			case Command::PASV: {
				cmd_PASV(controlConnectionfd);
			} break;
			case Command::ABOR: {
				cmd_ABOR(controlConnectionfd);
			} break;
			default: { cmd_INVALID(controlConnectionfd); } break;
		}

		// previous command tracking
		previousCommand = currentCommand;
		currentCommand = commandType;

		// reset PORT to default after one command
		if (previousCommand == Command::PORT) {
			resetDataConnectionIP();
			resetDataConnectionPortNumber();
		}

	}  // end:while

}  // end:function