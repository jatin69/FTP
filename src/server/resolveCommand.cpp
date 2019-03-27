#include "./server.hpp"

Server::Command Server::resolveCommand(const std::string& incomingCommand) {
    string cmd(incomingCommand);
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), std::ptr_fun<int, int>(std::toupper));
    
    if(cmd.compare("NOOP") == 0) return Command::NOOP;
    return Command::INVALID;
}
