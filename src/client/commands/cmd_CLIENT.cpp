#include "./../client.hpp"

/**Client commands 
 * Commands that begin with `!` are to be executed on client.
 *
 * All commands are supported.
 * 
 * Supported shell builtins - 
 * `cd`.
 * 
*/

void Client::cmd_CLIENT(const string& cmd) {
    
    string commandResponse;

    if(cmd.rfind("cd ")==0){
        string pathToChange = cmd.substr(3, cmd.size());
        int stat = chdir(pathToChange.c_str());
        if (stat == 0) {
            commandResponse = "Directory successfully changed.";
        } else {
            commandResponse = "Failed to change directory.";
        }
    }
    else{
        commandResponse = executeShellCommand(cmd);
    }
    // @logging
    logs(commandResponse.c_str());
}
