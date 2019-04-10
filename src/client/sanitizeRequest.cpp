#include "./client.hpp"

/**sanitize request
 * 
 * user can enter anything. It is our job to ensure he does not break system.
 * A few measures a being taken to avoid the same.
 * 
 * @usage
 * disallow anything after semicolon
 * support nickname facility
 * 
*/
string Client::sanitizeRequest(const string& req) {

    // disallow semicolon, truncate all after semicolon
    string saneCommand(req.substr(0, req.find(";")));
    string cmd((saneCommand=="") ? "noop" : saneCommand);

    string originalCommand;
    string nickName;

    // nickname, originalCommand
    vector<pair<string, string>> commandPairs = {
        { "ls", "LIST" },
        { "cd", "CWD"  },
        { "pwd", "PWD" },
        { "mkdir", "MKD"},
        { "rmdir", "RMD"},
        { "get", "RETR"}, { "GET", "RETR"},
        { "put", "STOR"}, { "PUT", "STOR"},
        { "exit", "QUIT"}
    };

    for(auto it : commandPairs) {
        nickName = it.first;
        originalCommand = it.second;
        if (cmd.compare(0, nickName.length(), nickName) == 0){
            if(cmd.length() > nickName.length()){
                if(isspace(cmd.at(nickName.length()))){
                    cmd = originalCommand + cmd.substr(nickName.length(), cmd.length());
                    break;        
                }
            }
            else{
                cmd = originalCommand + cmd.substr(nickName.length(), cmd.length());
                break;
            }
        }
    }

    string detectedCommand("Detected Command : ");
    detectedCommand.append(cmd);
    // @logging
    // logs(detectedCommand.c_str());
    
    return cmd;
}