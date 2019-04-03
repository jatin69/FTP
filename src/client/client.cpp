#include "./client.hpp"

// Protocol Interpreter for Server
void Client::initiateProtocolInterpreter(int controlConnectionfd) {

    string msgFromServer;
    Recv(controlConnectionfd, msgFromServer);
    logs(msgFromServer.c_str());

    if(authenticateFromServer(controlConnectionfd) == 0){
        cmd_QUIT(controlConnectionfd);
        return;
    }
 
    string ftpRequest;
    string ftpResponse;
     
    Command previousCommand = Command::INVALID;
    Command currentCommand = Command::INVALID;   
 
    while(true) {
        cout<<"J-FTP ➜ ";
		getline(std::cin, ftpRequest);

        // handling ctrl+D
        if(cin.eof()){
              ftpRequest = "QUIT";
        }
        
        // handling empty line
        if (ftpRequest.size() == 0) {    
          continue;
        }

        logv(ftpRequest);

        ftpRequest = sanitizeRequest(ftpRequest);

        vector<string> tokens = commandTokenizer(ftpRequest);
        logs("Command Tokenizer");
        for(auto it : tokens){ cout << it << "\n"; }    // @todo : remove log
        Command commandType = resolveCommand(tokens.front());
        // logv(commandType);
        switch (commandType) {
            case Command::USER : { 
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_USER(controlConnectionfd, tokens);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Provide username for login");
                    printf("\nUsage\n\t%s\n\n", "USER <username>");
                }
            }break;
            
            case Command::PASS : { 
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_PASS(controlConnectionfd, tokens);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Provide password for login");
                    printf("\nUsage\n\t%s\n\n", "PASS <password>");
                }
            }break;
            
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

            case Command::TYPE : { 
                if(tokens.size() == 3){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_TYPE(controlConnectionfd, tokens);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Switch the representation type");
                    printf("\nUsage\n\t%s\n\t%s\n\n", "TYPE <A/E/I> <N/T/C>", "TYPE L <byte size>");
                }
            } break;
            
            case Command::MODE : { 
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_MODE(controlConnectionfd, tokens);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Switch the transfer mode");
                    printf("\nUsage\n\t%s", "MODE <S/B/C>");
                    printf("\n\t%s\n\n", "Namely, Stream, Block, Compressed Mode");
                }
            }break;

            case Command::STRU : { 
                if(tokens.size() == 2){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_STRU(controlConnectionfd, tokens);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Switch the File structure Type  ");
                    printf("\nUsage\n\t%s", "STRU <F/R/P>");
                    printf("\n\t%s\n\n", "Namely, File, Record Structure, Page Structure");
                }
            }break;
            
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

            case Command::CDUP: {    
                if(tokens.size() == 1){
                    Send(controlConnectionfd, ftpRequest);
                    cmd_CDUP(controlConnectionfd);
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Change to parent directory");
                    printf("\nUsage\n\t%s\n\n", "CDUP");
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

        // case Command::PASV      : { cmd_PASV     (controlConnectionfd);    } break;
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

