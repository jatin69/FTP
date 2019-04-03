#include "./server.hpp"

int Server::authenticateClient(int controlConnectionfd) {
        
    string ftpUser = "";
    string ftpPassword = "";

    while(true) {
        string commandString;
        Recv(controlConnectionfd, commandString);
        logr(commandString.c_str());                    // @todo : remove log

        vector<string> tokens = commandTokenizer(commandString);
        logs("Command Tokenizer");
        for(auto it : tokens){ cout << it << "\n"; }    // @todo : remove log

        Command commandType = resolveCommand(tokens.front());
        // logv(commandType);

        switch (commandType){

            case Command::USER      : { 
                ftpUser = cmd_USER (controlConnectionfd, tokens);
            } break;
            case Command::PASS      : { 
                if(ftpUser == ""){
                    Send(controlConnectionfd, "Specify USER first", 220);
                    continue;
                }
                return cmd_PASS (controlConnectionfd, tokens, ftpUser);

            } break;

            case Command::QUIT      : { 
                cmd_QUIT (controlConnectionfd);         
            } break;

            default                 : { 
                Send(controlConnectionfd, "Unauthenticated User. Please Login first", 331);
                ftpUser = "";
                ftpPassword = "";
            } break;
        }
    }
}