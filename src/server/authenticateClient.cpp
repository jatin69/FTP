#include "./server.hpp"

/**Authenticate client
 *
 * @usage
 * Before client can access server's file system or any other commands,
 * it has to go through authentication.
 *
*/
void Server::authenticateClient(int controlConnectionfd) {
	while (true) {
		string commandString;
		Recv(controlConnectionfd, commandString);
		// @logging
		fprintf(stdout, "\n[INFO][REQUEST] : %s", commandString.c_str());


		vector<string> tokens = commandTokenizer(commandString);
		// @logging
		// logs("Command Tokenizer");
		// for(auto it : tokens){ cout << it << "\n"; }

		Command commandType = resolveCommand(tokens.front());
		// @logging
		// logv(commandType);

		switch (commandType) {
			case Command::USER: {
				cmd_USER(controlConnectionfd, tokens);
			} break;

			case Command::PASS: {
				if (getClientUsername() == "") {
					Send(controlConnectionfd, "Specify USER first", 503);
					continue;
				} else {
					cmd_PASS(controlConnectionfd, tokens);
					return;
				}
			} break;

			case Command::QUIT: {
				cmd_QUIT(controlConnectionfd);
			} break;

			default: {
				Send(controlConnectionfd, "Unauthenticated User. Please Login first",
					 530);
			} break;
		}
	}
}