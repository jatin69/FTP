#include "./client.hpp"

/**Protocol Interpretor for client
 *
 * Classic FTP has two parts.
 * The PI to interpret commands, and the data connection to transfer files.
 *
*/
void Client::initiateProtocolInterpreter(int controlConnectionfd) {
	// begin
	string msgFromServer;
	Recv(controlConnectionfd, msgFromServer);
	logs(msgFromServer.c_str());

	// authentication
	// if (authenticateFromServer(controlConnectionfd) == 0) {
	// 	cmd_QUIT(controlConnectionfd);
	// 	return;
	// }

	string ftpRequest;
	string ftpResponse;

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
		cout << "J-FTP ➜ ";
		getline(std::cin, ftpRequest);
		ftpRequest = trim(ftpRequest);

		// handling ctrl+D
		if (cin.eof()) {
			ftpRequest = "QUIT";
		}

		// handling empty line
		if (ftpRequest.size() == 0) {
			continue;
		}

		ftpRequest = sanitizeRequest(ftpRequest);
		// @logging
		logv(ftpRequest);

		// tokenize command
		vector<string> tokens = commandTokenizer(ftpRequest);

		// resolve command type from first word
		Command commandType = resolveCommand(tokens.front());

		switch (commandType) {
			case Command::CLIENT: {
				cmd_CLIENT(ftpRequest);
			} break;

			case Command::HELP: {
				cmd_HELP(ftpRequest);
			} break;

			case Command::USER: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_USER(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Provide username for login");
					printf("\nUsage\n\t%s\n\n", "USER <username>");
				}
			} break;

			case Command::PASS: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_PASS(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Provide password for login");
					printf("\nUsage\n\t%s\n\n", "PASS <password>");
				}
			} break;

			case Command::PORT: {
				if (tokens.size() == 3) {
					Send(controlConnectionfd, ftpRequest);
					cmd_PORT(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Switch data connection IP, Port");
					printf("\nUsage\n\t%s\n\n", "PORT <IPAddress> <Port>");
				}
			} break;

			case Command::LIST: {
				if (tokens.size() >= 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_LIST(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "List directory contents");
					printf("\nUsage\n\t%s\n\t%s\n\n", "LIST <pathToDirectory>",
						   "ls <pathToDirectory>");
				}
			} break;

			case Command::CWD: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_CWD(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Change working directory");
					printf("\nUsage\n\t%s\n\t%s\n\n", "CWD <path>", "cd <path>");
				}
			} break;

			case Command::MKD: {
				if (tokens.size() >= 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_MKD(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Make directory");
					printf("\nUsage\n\t%s\n\t%s\n\n", "MKD <directoryName>",
						   "mkdir <directoryName>");
				}
			} break;

			case Command::RMD: {
				if (tokens.size() >= 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_MKD(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Remove directory");
					printf("\nUsage\n\t%s\n\t%s\n\n", "RMD <directoryName>",
						   "rmdir <directoryName>");
				}
			} break;

			case Command::STOR: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_STOR(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Send File to Server");
					printf("\nUsage\n\t%s\n\t%s\n\n", "STOR <fileName>",
						   "put <fileName>");
				}
			} break;

			case Command::RETR: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_RETR(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Retrive File from Server");
					printf("\nUsage\n\t%s\n\t%s\n\n", "RETR <fileName>",
						   "get <fileName>");
				}
			} break;

			case Command::TYPE: {
				if (tokens.size() == 3) {
					Send(controlConnectionfd, ftpRequest);
					cmd_TYPE(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Switch the representation type");
					printf("\nUsage\n\t%s\n\t%s\n\n", "TYPE <A/E/I> <N/T/C>",
						   "TYPE L <byte size>");
				}
			} break;

			case Command::MODE: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_MODE(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Switch the transfer mode");
					printf("\nUsage\n\t%s", "MODE <S/B/C>");
					printf("\n\t%s\n\n", "Namely, Stream, Block, Compressed Mode");
				}
			} break;

			case Command::STRU: {
				if (tokens.size() == 2) {
					Send(controlConnectionfd, ftpRequest);
					cmd_STRU(controlConnectionfd, tokens);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Switch the File structure Type  ");
					printf("\nUsage\n\t%s", "STRU <F/R/P>");
					printf("\n\t%s\n\n",
						   "Namely, File, Record Structure, Page Structure");
				}
			} break;

			case Command::NOOP: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_NOOP(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "No Operation");
					printf("\nUsage\n\t%s\n\n", "NOOP");
				}
			} break;

			case Command::SYS: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_SYS(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Get System Details Of server");
					printf("\nUsage\n\t%s\n\n", "SYS");
				}
			} break;

			case Command::PWD: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_PWD(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Print working directory");
					printf("\nUsage\n\t%s\n\n", "PWD");
				}
			} break;

			case Command::CDUP: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_CDUP(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Change to parent directory");
					printf("\nUsage\n\t%s\n\n", "CDUP");
				}
			} break;

			case Command::QUIT: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_QUIT(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Quit the application");
					printf("\nUsage\n\t%s\n\n", "QUIT");
				}
			} break;

			case Command::PASV: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_PASV(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s", "Switch to Passive Receive Mode");
					printf("\nUsage\n\t%s\n\n", "PASV");
				}
			} break;

			case Command::ABOR: {
				if (tokens.size() == 1) {
					Send(controlConnectionfd, ftpRequest);
					cmd_ABOR(controlConnectionfd);
				} else {
					printf("\nINVALID USAGE\n");
					printf("\nCommand\n\t%s",
						   "Abort the last command and related data transfer");
					printf("\nUsage\n\t%s\n\n", "ABOR");
				}
			} break;

			default: {
				Send(controlConnectionfd, ftpRequest);
				cmd_INVALID(controlConnectionfd);
			} break;
		}

		// previous command tracking
		previousCommand = currentCommand;
		currentCommand = commandType;

		// reset PORT to default after one command
		if (previousCommand == Command::PORT) {
			resetDataDumpReceiverIP();
			resetDataDumpReceiverPortNumber();
		}

	}  // end:while

}  // end:function