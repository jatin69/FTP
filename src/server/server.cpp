#include "./server.hpp"

void Server::initiateProtocolInterpreter(int controlConnectionfd) {
    
    Send(controlConnectionfd, "J's FTP-Server ", 220);
    
    if(authenticateClient(controlConnectionfd) == 0){
        Send(controlConnectionfd, "[AUTHENTICATION:FAILURE] Retry");
        return;
    }
 
    Command previousCommand = Command::INVALID;
    Command currentCommand = Command::INVALID;   

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
            case Command::PORT      : { cmd_PORT     (controlConnectionfd, tokens);    } break;
            case Command::LIST      : { cmd_LIST     (controlConnectionfd, tokens);    } break;
            case Command::CWD       : { cmd_CWD      (controlConnectionfd, tokens);    } break;
            case Command::MKD       : { cmd_MKD      (controlConnectionfd, tokens);    } break;
            case Command::RMD       : { cmd_RMD      (controlConnectionfd, tokens);    } break;
            case Command::STOR      : { cmd_STOR     (controlConnectionfd, tokens);    } break;
            case Command::RETR      : { cmd_RETR     (controlConnectionfd, tokens);    } break;
            // case Command::TYPE      : { cmd_TYPE     (controlConnectionfd, tokens);    } break;
            // case Command::MODE      : { cmd_MODE     (controlConnectionfd, tokens);    } break;
            // case Command::STRU      : { cmd_STRU     (controlConnectionfd, tokens);    } break;
            
            case Command::NOOP      : { cmd_NOOP     (controlConnectionfd);    } break;
            case Command::SYS       : { cmd_SYS      (controlConnectionfd);    } break;
            // case Command::PASV      : { cmd_PASV     (controlConnectionfd);    } break;
            case Command::PWD       : { cmd_PWD      (controlConnectionfd);    } break;
            // case Command::QUIT      : { cmd_QUIT     (controlConnectionfd);    } break;
            // case Command::ABOR      : { cmd_ABOR     (controlConnectionfd);    } break;
            default                 : { cmd_INVALID  (controlConnectionfd);    } break;
        }

        // keeping track of previous command and current command
        previousCommand = currentCommand;
        currentCommand = commandType;

        if(previousCommand == Command::PORT) {
            resetDataConnectionIP();
            resetDataConnectionPortNumber();
        }

    }
}