#include "./../server.hpp"

void Server::cmd_RETR(int controlConnectionfd, const vector<string>& args){
    
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
            Send(controlConnectionfd, "Server Sent File Successfully.");
            logs("Server Sent File Successfully.");
        }
        else{
            Send(controlConnectionfd, "Resuming current connection.");
        }
        
        string ftpResponse;
        Recv(controlConnectionfd, ftpResponse);
        logs(ftpResponse.c_str());

    }

    if(pid==0) {        // child
        
        // child does not need control connection
        // close(controlConnectionfd);

        int dataConnectionfd = createDataConnection(controlConnectionfd);  
        // int dataConnectionfd = controlConnectionfd;
        
        logs(getDataConnectionIP());
        logv(getDataConnectionPortNumber());
        
        Send(dataConnectionfd, "Sending File in Binary Mode.", 150);
        
        string fileName(args[1]);
        SendFile(dataConnectionfd, fileName);
        // dont send anything else now. 
        // Client knows about completion because of connection termination.
        close(dataConnectionfd);        
        
        logs("File Sent.");
        // child will exit upon completion of its task
        exit(0);
    }
}
