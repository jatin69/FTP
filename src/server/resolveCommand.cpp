#include "./server.hpp"

/**Resolve the incoming token into a command.
 *
 * Whenever a new command is to be implemented, its entry must also be done here.
*/
Server::Command Server::resolveCommand(const string& incomingCommandToken) {
	string cmd(incomingCommandToken);
	std::transform(cmd.begin(), cmd.end(), cmd.begin(),
				   std::ptr_fun<int, int>(std::toupper));

	if (cmd.compare("USER") == 0)
		return Command::USER;
	if (cmd.compare("PASS") == 0)
		return Command::PASS;

	if (cmd.compare("NOOP") == 0)
		return Command::NOOP;
	if (cmd.compare("SYS") == 0)
		return Command::SYS;

	if (cmd.compare("PORT") == 0)
		return Command::PORT;
	if (cmd.compare("PASV") == 0)
		return Command::PASV;

	if (cmd.compare("LIST") == 0)
		return Command::LIST;
	if (cmd.compare("PWD") == 0)
		return Command::PWD;
	if (cmd.compare("CWD") == 0)
		return Command::CWD;
	if (cmd.compare("CDUP") == 0)
		return Command::CDUP;

	if (cmd.compare("MKD") == 0)
		return Command::MKD;
	if (cmd.compare("RMD") == 0)
		return Command::RMD;

	if (cmd.compare("STOR") == 0)
		return Command::STOR;
	if (cmd.compare("RETR") == 0)
		return Command::RETR;

	if (cmd.compare("TYPE") == 0)
		return Command::TYPE;
	if (cmd.compare("MODE") == 0)
		return Command::MODE;
	if (cmd.compare("STRU") == 0)
		return Command::STRU;

	if (cmd.compare("QUIT") == 0)
		return Command::QUIT;
	if (cmd.compare("ABOR") == 0)
		return Command::ABOR;

	return Command::INVALID;
}
