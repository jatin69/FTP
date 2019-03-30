#include "./client.hpp"

// Protocol Interpreter for Server
void Client::initiateProtocolInterpreter(int controlConnectionfd) {

    string msgFromServer;
    Recv(controlConnectionfd, msgFromServer);
    logs(msgFromServer.c_str());

    string ftpRequest;
    string ftpResponse;
    
    Command previousCommand = Command::INVALID;
    Command currentCommand = Command::INVALID;   
 
    while(true) {
        cout<<"J-FTP ➜ ";
		getline(std::cin, ftpRequest);
        logv(ftpRequest);

        // @todo : make this function to support ls etc
        ftpRequest = sanitizeRequest(ftpRequest);
        Send(controlConnectionfd, ftpRequest);

        vector<string> tokens = commandTokenizer(ftpRequest);
        logs("Command Tokenizer");
        for(auto it : tokens){ cout << it << "\n"; }    // @todo : remove log
        Command commandType = resolveCommand(tokens.front());
        // logv(commandType);
        switch (commandType) {
            
            case Command::PORT: {   cmd_PORT(controlConnectionfd, tokens);  } break;
            case Command::LIST: {   cmd_LIST(controlConnectionfd, tokens);  } break;
            case Command::CWD : {   cmd_CWD (controlConnectionfd, tokens);  } break;
            case Command::MKD : {   cmd_MKD (controlConnectionfd, tokens);  } break;
            case Command::RMD : {   cmd_RMD (controlConnectionfd, tokens);  } break;
            case Command::STOR: {   cmd_STOR (controlConnectionfd, tokens); } break;
            case Command::RETR: {   cmd_RETR  (controlConnectionfd, tokens);} break;
        // case Command::TYPE      : { cmd_TYPE     (controlfd, tokens);    }
        // break;
        // case Command::MODE      : { cmd_MODE     (controlfd, tokens);    }
        // break;
        // case Command::STRU      : { cmd_STRU     (controlfd, tokens);    }
        // break;

            case Command::NOOP: {   cmd_NOOP(controlConnectionfd);      } break;
            case Command::SYS: {    cmd_SYS(controlConnectionfd);       } break;
        // case Command::PASV      : { cmd_PASV     (controlfd);    } break;
            case Command::PWD: {    cmd_PWD(controlConnectionfd);       } break;
        // case Command::QUIT      : { cmd_QUIT     (controlfd);    } break;
        // case Command::ABOR      : { cmd_ABOR     (controlfd);    } break;
            default: { cmd_INVALID(controlConnectionfd); } break;
        }

        // keeping track of previous command and current command
        previousCommand = currentCommand;
        currentCommand = commandType;

        if(previousCommand == Command::PORT) {
            resetDataDumpReceiverIP();
            resetDataDumpReceiverPortNumber();
        }


    }
}

