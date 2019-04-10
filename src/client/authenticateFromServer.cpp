#include "./client.hpp"

/**Authenticate from server
 *
 * @usage
 * Before client can access server's file system or any other commands,
 * it has to go through authentication.
 * 
 * This function handles all commands prior to authentication.
 * 
 * Note that, the server is also in its authentication function when
 * this function is called, so the access space is very limited 
 * for un-authenticated client.
 *
*/
int Client::authenticateFromServer(int controlConnectionfd) {
         
    string ftpRequest;

    // command interpreter loop
    while(true) {
        
        cout<<"J-FTP ➜ ";
		getline(std::cin, ftpRequest);
        ftpRequest = trim(ftpRequest);

        // handling ctrl+D
        if(cin.eof()){  ftpRequest = "QUIT";    }
        
        // handling empty line
        if (ftpRequest.size() == 0) { continue; }

        ftpRequest = sanitizeRequest(ftpRequest);
        // @logging
        logv(ftpRequest);

        // tokenize command
        vector<string> tokens = commandTokenizer(ftpRequest);
    
        // resolve command type from first word
        Command commandType = resolveCommand(tokens.front());
        
        switch (commandType) {

            case Command::CLIENT : {
                // remove `CLIENT-SIDE-COMMAND Identifier : @`
                ftpRequest.erase(ftpRequest.begin(), ftpRequest.begin()+ FTP::CLIENT_SIDE_COMMAND_IDENTIFIER.size());
                cmd_CLIENT(ftpRequest);
            }break;

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
                /**Note that -
                 * This request goes to server's `authenticateClient` function
                 * Where only `USER`, `PASS`, `QUIT` are recognised.
                 * All other strings are simply responded with
                 * `un-authenticated client`
                */
                Send(controlConnectionfd, ftpRequest);
                cmd_INVALID (controlConnectionfd); 
            } break;
        }
    }
}