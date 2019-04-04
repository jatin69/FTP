#include "./client.hpp"

int Client::authenticateFromServer(int controlConnectionfd) {
         
    string ftpRequest;
    while(true) {
        cout<<"J-FTP ➜ ";
		getline(std::cin, ftpRequest);
        ftpRequest = trim(ftpRequest);

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
                    string ftpUser = "This is a dummy variable kept for consistency across server and client";
                    return cmd_PASS(controlConnectionfd, tokens);      
                }
                else{
                    printf("\nINVALID USAGE\n");
                    printf("\nCommand\n\t%s", "Provide password for login");
                    printf("\nUsage\n\t%s\n\n", "PASS <password>");
                }
            }break;
            
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

            default: { 
                Send(controlConnectionfd, ftpRequest);
                cmd_INVALID (controlConnectionfd); 
            } break;
        }
    }
}