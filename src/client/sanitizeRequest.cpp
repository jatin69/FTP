#include "./client.hpp"

string Client::sanitizeRequest(const string& req) {

    // disallow semicolon, truncate all after semicolon
    string saneCommand(req.substr(0, req.find(";")));
    string cmd((saneCommand=="") ? "noop" : saneCommand);

    string originalCommand;
    string nickName;

    originalCommand = "LIST";
    nickName = "LS";

    // nickname, originalCommand
    vector<pair<string, string>> commandPairs = {
        { "ls", "LIST" },
        { "cd", "CWD"  },
        { "pwd", "PWD" },
        { "mkdir", "MKD"},
        { "rmdir", "RMD"},
        { "get", "RETR"}, { "GET", "RETR"},
        { "put", "STOR"}, { "PUT", "STOR"}
    };

    for(auto it : commandPairs) {
        nickName = it.first;
        originalCommand = it.second;
        if (cmd.compare(0, nickName.length(), nickName) == 0){
            cmd = originalCommand + cmd.substr(nickName.length(), cmd.length());
            break;
        }
    }

    string detectedCommand("Detected Command : ");
    detectedCommand.append(cmd);
    logs(detectedCommand.c_str());
    return cmd;
}