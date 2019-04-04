#include "./../server.hpp"

void Server::cmd_LIST(int controlConnectionfd, const vector<string>& tokens){
    
    int pid = fork();
    
    if(pid < 0){        // error
        printError();
        throw runtime_error("[SERVER:CMD:LIST] Fork Error");
    }

    if(pid > 0) {       // parent
        int statusOfChild;
        // waiting for this child's completion
        waitpid(pid, &statusOfChild, 0);
        
        int exitCodeOfChild;
        if ( WIFEXITED(statusOfChild) ) { 
            exitCodeOfChild = WEXITSTATUS(statusOfChild);
        } 
        
        if(exitCodeOfChild == 0){
            Send(controlConnectionfd, "Directory Listing Send OK.", 226);
        }
        else{
            Send(controlConnectionfd, "Resuming current connection.");
        }
    }

    if(pid==0) {        // child
        
        // child does not need control connection
        // close(controlConnectionfd);


        int dataConnectionfd = createDataConnection(controlConnectionfd);  
        // int dataConnectionfd = controlConnectionfd;
        
        logs(getDataConnectionIP());
        logv(getDataConnectionPortNumber());
        
        Send(dataConnectionfd, "Directory Listing is as follows :");
        string commandToExecute = "ls -l ";
        for(auto it=tokens.begin()+1; it!=tokens.end(); ++it){
            commandToExecute += " " + *it;
        }
        string outputOfCommand = executeShellCommand(commandToExecute);
        Send(dataConnectionfd, outputOfCommand);
        
        // child will exit upon completion of its task
        close(dataConnectionfd);        
        exit(0);
    }
}
