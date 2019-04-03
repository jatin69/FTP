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

        ftpRequest = sanitizeRequest(ftpRequest);

        vector<string> tokens = commandTokenizer(ftpRequest);
        logs("Command Tokenizer");
        for(auto it : tokens){ cout << it << "\n"; }    // @todo : remove log
        Command commandType = resolveCommand(tokens.front());
        // logv(commandType);
        switch (commandType) {
            
            case Command::PORT: {
                if(tokens.size() == 3){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_PORT(controlConnectionfd, tokens);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Switch data connection IP, Port");
                    printf("\nUsage\n\t%s\n\n", "PORT <IPAddress> <Port>");
                }
            } break;

            case Command::LIST: {
                if(tokens.size() >= 1){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_LIST(controlConnectionfd, tokens);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "List directory contents");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "LIST <pathToDirectory>", "ls <pathToDirectory>");
                }
            } break;
            
            case Command::CWD : {   
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_CWD (controlConnectionfd, tokens);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Change working directory");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "CWD <path>", "cd <path>");
                }
                
            } break;

            case Command::MKD : {
                if(tokens.size() >= 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_MKD (controlConnectionfd, tokens);  
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Make directory");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "MKD <directoryName>", "mkdir <directoryName>");
                }
                
            } break;
            case Command::RMD : {   
                if(tokens.size() >= 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_MKD (controlConnectionfd, tokens);  
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Remove directory");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "RMD <directoryName>", "rmdir <directoryName>");
                }
            } break;

            case Command::STOR: {   
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_STOR (controlConnectionfd, tokens);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Send File to Server");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "STOR <fileName>", "put <fileName>");
                }
            } break;

            case Command::RETR: {   
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_RETR  (controlConnectionfd, tokens);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Retrive File from Server");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "RETR <fileName>", "get <fileName>");
                }
            } break;
        // case Command::TYPE      : { cmd_TYPE     (controlfd, tokens);    }
        // break;
        // case Command::MODE      : { cmd_MODE     (controlfd, tokens);    }
        // break;
        // case Command::STRU      : { cmd_STRU     (controlfd, tokens);    }
        // break;

            case Command::NOOP: {   
                if(tokens.size() == 1){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_NOOP(controlConnectionfd);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "No Operation");
                    printf("\nUsage\n\t%s\n\n", "NOOP");
                }
            } break;

            case Command::SYS: {    
                if(tokens.size() == 1){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_SYS(controlConnectionfd);       
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Get System Details Of server");
                    printf("\nUsage\n\t%s\n\n", "SYS");
                }    
            } break;

        // case Command::PASV      : { cmd_PASV     (controlfd);    } break;
            case Command::PWD: {    
                if(tokens.size() == 1){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_PWD(controlConnectionfd);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Print working directory");
                    printf("\nUsage\n\t%s\n\n", "PWD");
                }
            } break;
            case Command::QUIT      : { 
                if(tokens.size() == 1){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_QUIT(controlConnectionfd);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Quit the application");
                    printf("\nUsage\n\t%s\n\n", "QUIT");
                }  
                } break;
        // case Command::ABOR      : { cmd_ABOR     (controlfd);    } break;
            default: { 
                Send(controlConnectionfd, ftpRequest);
                cmd_INVALID (controlConnectionfd); 
            } break;
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

