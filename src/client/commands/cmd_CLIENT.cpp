#include "./../client.hpp"

void Client::cmd_CLIENT(const string& cmd) {
    
    string commandResponse;
    // logs((string("RECEIVED CMD IS : ") + cmd).c_str());

    /**Supported Commands -
     *
     * Normal commands are passed on as it is. 
     * Only supported shell builtin is `cd`.
     * 
    */

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

    logs(commandResponse.c_str());
}
