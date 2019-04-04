#include "./server.hpp"

void Server::authenticateClient(int controlConnectionfd) {
        
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
                cmd_USER (controlConnectionfd, tokens); 
            } break;
            
            case Command::PASS      : { 
                if(getClientUsername() == ""){
                    Send(controlConnectionfd, "Specify USER first", 220);
                    continue;
                }
                else{
                    cmd_PASS (controlConnectionfd, tokens);
                    return;
                }
            } break;
            
            case Command::QUIT      : { 
                cmd_QUIT (controlConnectionfd);         
            } break;

            default                 : { 
                Send(controlConnectionfd, "Unauthenticated User. Please Login first", 331);
            } break;
        }
    }
}