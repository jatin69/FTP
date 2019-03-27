#include "./server.hpp"

void Server::initiateProtocolInterpreter(int controlfd) {
    
    Send(controlfd, "J's FTP-Server ", 220);
    
    if(authenticateClient(controlfd) == 0){
        Send(controlfd, "[AUTHENTICATION:FAILURE] Retry");
        return;
    }

    while(true) {
        string commandString;
        Recv(controlfd, commandString);
        logs("Command Received. ");
        logs(commandString.c_str());                    // @todo : remove log

        vector<string> tokens = commandTokenizer(commandString);
        logs("Command Tokenizer");
        for(auto it : tokens){ cout << it << "\n"; }    // @todo : remove log

        Command type = resolveCommand(tokens.front());
        switch (type){
            case Command::NOOP  : { cmd_NOOP    (controlfd);    } break;
            default             : { cmd_INVALID (controlfd);    } break;
        }

    }
}